#cmake ver 3.10.2

PROJECT( BallsAndHolesGame )

SET( HEADERS Board.h Objects.h I_GameModel.h I_GameView.h I_GameController.h GameModel.h GameView.h GameController.h )

SET( SOURCES main.cpp Board.cpp Objects.cpp GameModel.cpp GameView.cpp GameController.cpp )

ADD_EXECUTABLE( BallsAndHolesGame ${HEADERS} ${SOURCES} )