#cmake ver 3.10.2

PROJECT( BallsAndHolesGame )

SET( HEADERS Board.h Objects.h BallsAndHolesGame.h GameModel.h GameView.h GameController.h )

SET( SOURCES main.cpp Board.cpp Objects.cpp BallsAndHolesGame.cpp )

ADD_EXECUTABLE( BallsAndHolesGame ${HEADERS} ${SOURCES} )