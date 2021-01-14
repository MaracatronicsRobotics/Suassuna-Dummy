# Qt libs to import
QT += core    \
      gui     \
      widgets \
      network \
      opengl

# Project configs
TEMPLATE = app
DESTDIR  = ../bin
TARGET   = Armorial-Suassuna
VERSION  = 0.0.1

CONFIG += c++14 console
CONFIG -= app_bundle

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

# Project libs
LIBS *= -lprotobuf -lQt5Core

# Compiling .proto files
system(echo "Compiling protobuf files" && cd include/proto && protoc --cpp_out=../ *.proto && cd ../..)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Project source files
SOURCES += \
        include/grSim_Commands.pb.cc \
        include/grSim_Packet.pb.cc \
        include/grSim_Replacement.pb.cc \
        include/messages_robocup_ssl_detection.pb.cc \
        include/messages_robocup_ssl_geometry.pb.cc \
        include/messages_robocup_ssl_refbox_log.pb.cc \
        include/messages_robocup_ssl_robot_status.pb.cc \
        include/messages_robocup_ssl_wrapper.pb.cc \
        include/referee.pb.cc \
        include/ssl_game_controller_auto_ref.pb.cc \
        include/ssl_game_controller_common.pb.cc \
        include/ssl_game_controller_team.pb.cc \
        include/ssl_game_event.pb.cc \
        include/ssl_game_event_2019.pb.cc \
        include/ssl_referee.pb.cc \
        main.cpp \
        src/constants/constants.cpp \
        src/entities/actuator/actuator.cpp \
        src/entities/actuator/simulator/simactuator.cpp \
        src/entities/entity.cpp \
        src/entities/vision/vision.cpp \
        src/entities/world/world.cpp \
        src/entities/world/worldmap.cpp \
        src/exithandler.cpp \
        src/suassuna.cpp \
        src/utils/text/text.cpp \
        src/utils/timer/timer.cpp \
        src/utils/types/angle.cpp \
        src/utils/types/angularspeed.cpp \
        src/utils/types/position.cpp \
        src/utils/types/team.cpp \
        src/utils/types/velocity.cpp

# Project header files
HEADERS += \
    include/grSim_Commands.pb.h \
    include/grSim_Packet.pb.h \
    include/grSim_Replacement.pb.h \
    include/messages_robocup_ssl_detection.pb.h \
    include/messages_robocup_ssl_geometry.pb.h \
    include/messages_robocup_ssl_refbox_log.pb.h \
    include/messages_robocup_ssl_robot_status.pb.h \
    include/messages_robocup_ssl_wrapper.pb.h \
    include/referee.pb.h \
    include/ssl_game_controller_auto_ref.pb.h \
    include/ssl_game_controller_common.pb.h \
    include/ssl_game_controller_team.pb.h \
    include/ssl_game_event.pb.h \
    include/ssl_game_event_2019.pb.h \
    include/ssl_referee.pb.h \
    src/constants/constants.h \
    src/entities/actuator/actuator.h \
    src/entities/actuator/simulator/simactuator.h \
    src/entities/entity.h \
    src/entities/vision/vision.h \
    src/entities/world/world.h \
    src/entities/world/worldmap.h \
    src/exithandler.h \
    src/suassuna.h \
    src/utils/color/color.h \
    src/utils/text/text.h \
    src/utils/timer/timer.h \
    src/utils/types/angle.h \
    src/utils/types/angularspeed.h \
    src/utils/types/position.h \
    src/utils/types/team.h \
    src/utils/types/types.h \
    src/utils/types/typesNamespace.h \
    src/utils/types/velocity.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
