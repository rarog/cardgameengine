
CGE_VERSION_MAJOR = 0
CGE_VERSION_MINOR = 9
CGE_VERSION_PATCH = 0

CGE_VERSION = 0.9.0

DEFINES += CGE_VERSION_MAJOR=$$CGE_VERSION_MAJOR
DEFINES += CGE_VERSION_MINOR=$$CGE_VERSION_MINOR
DEFINES += CGE_VERSION_PATCH=$$CGE_VERSION_PATCH

DEFINES += CGE_VERSION=$$CGE_VERSION
DEFINES += CGE_STR_VERSION=\\\"$$CGE_VERSION\\\"

# Check the Qt version. If QT_VERSION is not set, it is probably Qt 3.
isEmpty(QT_VERSION) {
    error("QT_VERSION not defined. Tiled does not work with Qt 3.")
}
contains(QT_VERSION, ^4\\.[0-5]\\..*) {
    message("Cannot build Tiled with Qt version $$QT_VERSION")
    error("Use at least Qt 4.6")
}
