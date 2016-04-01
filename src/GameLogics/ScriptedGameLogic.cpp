
/*

Copyright 2011 Claus Ilginnis <Claus@Ilginnis.de>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.


*/

#include "ScriptedGameLogic.h"
#include <QByteArray>
#include <QFile>
#include "Cards/CardsModel.h"
#include <QScriptEngineDebugger>
#include <QMessageBox>
#include <QDebug>
#include <QMainWindow>
#include <QApplication>
#include "GameLogics/ScriptGameInterface.h"

typedef CardStack * CardStackPointer;

QScriptValue printToStdOut ( QScriptContext * context, QScriptEngine *  )
{
    for ( int i = 0 ; i < context->argumentCount() ; i++ )
    {
        qDebug() << "SCRIPT_PRINT: " << context->argument ( i ).toString();
    }
    return QScriptValue();
}

QScriptValue cardStackToScriptValue ( QScriptEngine * engine, const CardStackPointer  & s )
{
    //    CardStackWrapper * wrapper = new CardStackWrapper();
    //    wrapper->setCardStack(s);
    //    QObject * objectValue = wrapper;
    //    QScriptValue obj = engine->newQObject( objectValue , QScriptEngine::ScriptOwnership);

    QScriptValue obj = engine->newQObject (  s );
    return obj;
}

void cardStackFromScriptValue ( const QScriptValue & obj, CardStackPointer & s )
{
    s = dynamic_cast<CardStack *> ( obj.toQObject() );
}

Q_DECLARE_METATYPE ( CardStack * )

typedef Card * CardPointer;


QScriptValue cardToScriptValue ( QScriptEngine * engine, const CardPointer  & s )
{
    //    CardWrapper * wrapper = new CardWrapper();
    //    wrapper->setCard(s);
    //    QObject * objectValue = wrapper;
    //    QScriptValue obj = engine->newQObject( objectValue , QScriptEngine::ScriptOwnership);

    QScriptValue obj = engine->newQObject (  s );
    obj.setProperty ( "name", s->toString() );
    return obj;
}

void cardFromScriptValue ( const QScriptValue & obj, CardPointer & s )
{
    s = dynamic_cast<Card *> ( obj.toQObject() );
}

Q_DECLARE_METATYPE ( Card * )


ScriptedGameLogic::ScriptedGameLogic ( CardGame * parent ) :
    GameLogic ( parent )
{

}

void ScriptedGameLogic::init ( QString fileName )
{
    attachDebugger();

    QFile f ( fileName );
    if ( ! f.open ( QIODevice::ReadOnly ) )
    {
        return;
    }

    QString source = QString::fromLocal8Bit ( f.readAll() );
    // check syntax
    QScriptSyntaxCheckResult error = _engine.checkSyntax ( source );
    if ( error.state() != QScriptSyntaxCheckResult::Valid )
    {
        QString text = QString ( "Error: %1 in Line %2, Column %3" )
                       .arg ( error.errorMessage() )
                       .arg ( error.errorLineNumber() )
                       .arg ( error.errorColumnNumber() );
        QMessageBox::critical ( NULL, tr ( "Syntax Error" ), text );
    }

    QScriptProgram program ( source, fileName );
    _engine.evaluate ( program );

    addBuiltInObjects();

    callFunction ( "init" );
}

void ScriptedGameLogic::attachDebugger()
{
    QScriptEngineDebugger * newDebugger = new QScriptEngineDebugger ( this );
    newDebugger->attachTo ( &_engine );
    QList<QWidget *> widgets = qApp->allWidgets();

    foreach ( QWidget * widget, widgets )
    {
        QMainWindow * mainWindow = dynamic_cast<QMainWindow *> ( widget );
        if ( mainWindow != NULL )
        {
            //QMenu * menu=newDebugger->createStandardMenu( mainWindow );
            QToolBar * bar = newDebugger->createStandardToolBar ( mainWindow );
            mainWindow->addToolBar ( bar );
        }
    }
}


void ScriptedGameLogic::setGame ( CardGame * parent )
{
    setParent ( parent );
    _game = parent;
}

void ScriptedGameLogic::clickedOnCard ( QString id )
{
    QScriptValueList args;
    QString stackName = _game->cards().stackNameForId ( id );

    Card * card = _game->cards().cardForId ( id );

    args << stackName << _engine.newQObject ( card );

    callFunction ( "onCardClick", args );
    emit gameStateChanged();
}

void ScriptedGameLogic::doubleClickedOnCard ( QString id )
{
    QScriptValueList args;

    QString stackName = _game->cards().stackNameForId ( id );
    Card * card = _game->cards().cardForId ( id );

    args << stackName << _engine.newQObject ( card );
    args << _engine.newQObject ( card );

    callFunction ( "onCardDoubleClick", args );
    emit gameStateChanged();
}

void ScriptedGameLogic::wantsToMoveItem ( QStringList cardIds, QString destinationCardId )
{
    QScriptValueList args;

    Card * destinationCard = _game->cards().cardForId ( destinationCardId );

    args << cardIdListToScriptValue ( cardIds );
    args << _engine.newQObject ( destinationCard );
    args << _game->cards().stackNameForId ( cardIds[0] );
    args << _game->cards().stackNameForId ( destinationCardId );

    callFunction ( "onCardMovedOnAnOther", args );
    emit gameStateChanged();
}

void ScriptedGameLogic::wantsToMoveItem ( QStringList cardIds, QPoint stackCoordinate )
{
    QScriptValueList args;

    //TODO gett stack name by position not id
    QString stackName = _game->cards().stackNameForId ( cardIds[0] );

    args << cardIdListToScriptValue ( cardIds );
    args << stackName;
    args << _game->cards().stackNameAtPos ( stackCoordinate );

    callFunction ( "onCardMovedOnAnEmptyStack", args );
    emit gameStateChanged();
}

QScriptValue ScriptedGameLogic::callFunction ( QString functionName, QScriptValueList & args )
{
    QScriptValue myFunc = _engine.globalObject().property ( functionName );

    Q_ASSERT ( myFunc.isValid() );
    Q_ASSERT ( myFunc.isFunction() );

    QScriptValue result = myFunc.call ( QScriptValue(), args );

    _game->cards().testForOrphanedCards();

    return result;
}

QScriptValue ScriptedGameLogic::cardIdListToScriptValue ( QStringList idList )
{
    QScriptValue result;
    result = _engine.newArray ( idList.length() );
    for ( int i = 0 ; i < idList.length() ; i++ )
    {
        QScriptValue o = _engine.newQObject ( _game->cards().cardForId ( idList[i] ) );
        result.setProperty ( i, o );
    }
    return result;
}

void ScriptedGameLogic::clickedOnStack ( QPoint id )
{
    QScriptValueList args;

    QString stackName = _game->cards().stackNameAtPos ( id );

    args << stackName;

    callFunction ( "onEmptyStackClicked", args );
    emit gameStateChanged();
}

void ScriptedGameLogic::doubleClickedOnStack ( QPoint id )
{
    QScriptValueList args;

    args << _game->cards().stackNameAtPos ( id );

    callFunction ( "onEmptyStackDoubleClicked", args );
    emit gameStateChanged();
}

void ScriptedGameLogic::addBuiltInObjects()
{
    // register converters for card and cardstack
    qScriptRegisterMetaType<CardStack *> ( &_engine, cardStackToScriptValue, cardStackFromScriptValue );
    qScriptRegisterMetaType<Card *> ( &_engine, cardToScriptValue, cardFromScriptValue );

    // add an alternate print function
    QScriptValue printFunction = _engine.newFunction ( printToStdOut, 1 );
    _engine.globalObject().setProperty ( "print", printFunction );

    // add the cards model
    QObject * cardModelObject = &_game->cards();
    QScriptValue objectValue = _engine.newQObject ( cardModelObject );
    _engine.globalObject().setProperty ( "cards", objectValue );

    // add a ame-script interface
    ScriptGameInterface * gameInterface = new ScriptGameInterface ( &_engine, _game , this );
    gameInterface->initPlayerVariables();
    objectValue = _engine.newQObject ( gameInterface );
    _engine.globalObject().setProperty ( "game", objectValue );
    bool bOk = connect ( gameInterface, SIGNAL ( gameOver ( QScriptValue ) ), this, SLOT ( gameOverSlot ( QScriptValue ) ) );
    Q_ASSERT ( bOk );
}

void ScriptedGameLogic::gameOverSlot ( QScriptValue winnerId )
{
    emit gameOver ( winnerId.toString() );
}
