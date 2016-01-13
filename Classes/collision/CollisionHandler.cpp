#include "collision/CollisionHandler.h"

TMXLayer* CollisionHandler::_layer = NULL;
LevelBackground* CollisionHandler::_levelback = NULL;

CollisionInfo CollisionHandler::getCollisionInfo(std::string currentStatusDescription, Vec2 position)
/// El valor de retorno indica en que lado del tile se produce la colision
{
    CollisionInfo info;

	CollisionHandler::checkBackgroundCollision(position, currentStatusDescription, info);
	CollisionHandler::checkBounds(position, info);
	
    return info;


}

void CollisionHandler::checkBounds(Vec2 position, CollisionInfo &info)
{
	Vec2 mapSize = _levelback->getTileMapSizeInPixels();
	
	info.setRightCollision(info.isRightCollision() || position.x <= 0);
	info.setLeftCollision(info.isLeftCollision() || position.x >= mapSize.x);
	info.setDownCollision(info.isDownCollision() || position.y >= mapSize.y);/// REVISAR POR QUE NO ANDA!
	info.setUpCollision(info.isUpCollision() ||  position.y <= 0);/// REVISAR POR QUE NO ANDA!
	
}

void CollisionHandler::checkBackgroundCollision(Vec2 position, std::string currentStatusDescription, CollisionInfo &info)
{
	
	Vec2 tileSize = _levelback->getTileSizeInPixels();
	
	float xTile = tileSize.x;
	float yTile = tileSize.y;

	Vec2 leftPosition(position.x - xTile/2, position.y); //Punto de colision a izquierda del player
	Vec2 rightPosition(position.x + xTile/2, position.y); //Punto de colision a derecha del player
	Vec2 upPosition(position.x, position.y + yTile/2); //Punto de colision a izquierda del player
	Vec2 downPosition(position.x, position.y - yTile/2); //Punto de colision a izquierda del player

	Vec2 upRightPosition(position.x + xTile/2, position.y + yTile/2); //Punto de colision a izquierda del player
	Vec2 downRightPosition(position.x + xTile/2, position.y - yTile/2); //Punto de colision a izquierda del player
	Vec2 upLeftPosition(position.x - xTile/2, position.y + yTile/2); //Punto de colision a izquierda del player
	Vec2 downLeftPosition(position.x - xTile/2, position.y - yTile/2); //Punto de colision a izquierda del player

    Vec2 tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(downPosition); /// Posicion del tile dentro de la matriz del tilemap (fila, columna)
    Vec2 tileCoord = CollisionHandler::_levelback->getForegroundLayer()->getPositionAt(tilePosition); /// Posicion del tile en el mundo (x,y)

    Vec2 tileUpPosition(tileCoord.x, tileCoord.y + yTile);


    int tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);

    /*** COLISION DESDE ARRIBA DEL TILE ***/
    if(tileGID)
    {
        ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();
        if(flags.at("Up").asString() == "true" && downPosition.y >= tileUpPosition.y)
    	// Valido la colision contra el suelo solo cuando la posicion del player es mayor al limite superior del tile

        {


            if(currentStatusDescription == FALL_LEFT_ID ||
               currentStatusDescription == FALL_RIGHT_ID ||
               currentStatusDescription == WALK_RIGHT_ID ||
               currentStatusDescription == WALK_LEFT_ID ||
               currentStatusDescription == STAND_RIGHT_ID ||
               currentStatusDescription == STAND_LEFT_ID)
            {
                info.setUpCollision(true);
            }
        }
		
		if(flags.at("Transition").asString() == "true")
		{
			info.setTransition(true);
		}
    }

    //Valido la colision desde arriba tomando los puntos diagonales del player
	tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(downRightPosition);
    tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
	if(tileGID)
	{
		ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();
		if(flags.at("Up").asString() == "true" && downRightPosition.y >= tileUpPosition.y)
		{


			if(currentStatusDescription == FALL_LEFT_ID ||
			   currentStatusDescription == FALL_RIGHT_ID ||
			   currentStatusDescription == WALK_RIGHT_ID ||
			   currentStatusDescription == WALK_LEFT_ID ||
			   currentStatusDescription == STAND_RIGHT_ID ||
			   currentStatusDescription == STAND_LEFT_ID)
			{
				info.setUpCollision(true);
			}
		}

		if(flags.at("Transition").asString() == "true")
		{
			info.setTransition(true);
		}
	}

	tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(downLeftPosition);
	tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
	if(tileGID)
	{
		ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();
		if(flags.at("Up").asString() == "true" && downLeftPosition.y >= tileUpPosition.y)
		{


			if(currentStatusDescription == FALL_LEFT_ID ||
			   currentStatusDescription == FALL_RIGHT_ID ||
			   currentStatusDescription == WALK_RIGHT_ID ||
			   currentStatusDescription == WALK_LEFT_ID ||
			   currentStatusDescription == STAND_RIGHT_ID ||
			   currentStatusDescription == STAND_LEFT_ID)
			{
				info.setUpCollision(true);
			}
		}

		if(flags.at("Transition").asString() == "true")
		{
			info.setTransition(true);
		}
	}
	/*** FIN COLISION DESDE ARRIBA DEL TILE ***/

	/*** COLISION A IZQUIERDA DEL TILE ***/
	tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(rightPosition);
    tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
    if(tileGID)
    {
		ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();
	    if(flags.at("Left").asString() == "true")
        {
            if(currentStatusDescription == FALL_RIGHT_ID ||
               currentStatusDescription == JUMP_RIGHT_ID ||
               currentStatusDescription == WALK_RIGHT_ID ||
			   currentStatusDescription == STAND_RIGHT_ID ||
               currentStatusDescription == STAND_LEFT_ID)
            {
                info.setLeftCollision(true);
            }
        }
		
		if(flags.at("Transition").asString() == "true")
		{
			info.setTransition(true);
		}
	}
    if(!info.isUpCollision())
    {
		tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(upRightPosition);
		tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
		if(tileGID)
		{
			ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();
			if(flags.at("Left").asString() == "true")
			{
				if(currentStatusDescription == FALL_RIGHT_ID ||
				   currentStatusDescription == JUMP_RIGHT_ID ||
				   currentStatusDescription == WALK_RIGHT_ID ||
				   currentStatusDescription == STAND_RIGHT_ID ||
				   currentStatusDescription == STAND_LEFT_ID)
				{
					info.setLeftCollision(true);
				}
			}

			if(flags.at("Transition").asString() == "true")
			{
				info.setTransition(true);
			}
		}
		tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(downRightPosition);
		tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
		if(tileGID)
		{
			ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();
			if(flags.at("Left").asString() == "true")
			{
				if(currentStatusDescription == FALL_RIGHT_ID ||
				   currentStatusDescription == JUMP_RIGHT_ID ||
				   currentStatusDescription == WALK_RIGHT_ID ||
				   currentStatusDescription == STAND_RIGHT_ID ||
				   currentStatusDescription == STAND_LEFT_ID)
				{
					info.setLeftCollision(true);
				}
			}

			if(flags.at("Transition").asString() == "true")
			{
				info.setTransition(true);
			}
		}
    }

    /*** FIN COLISION A IZQUIERDA DEL TILE ***/

    /*** COLISION A DERECHA DEL TILE ***/
    if(!info.isUpCollision())
    /// Las validaciones de colision a derecha en los puntos diagonales solo se deben hacer si no fue detectada una colision desde arriba,
    /// esto es así, ya que en caso de haber colision desde arriba y a derecha desde un punto diagonal, el player no podria moverse en caso
    /// de colisionar en la esquina de un tile ya que se detectaria una colision hacia derecha sin que haya obstaculo real al player!
    {
		tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(upLeftPosition);
		tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
		if(tileGID)
		{
			ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();

			if(flags.at("Right").asString() == "true")
			{
				 if(currentStatusDescription == FALL_LEFT_ID ||
					currentStatusDescription == JUMP_LEFT_ID ||
					currentStatusDescription == WALK_LEFT_ID ||
					currentStatusDescription == STAND_RIGHT_ID ||
					currentStatusDescription == STAND_LEFT_ID)
				{
					info.setRightCollision(true);
				}
			}

			if(flags.at("Transition").asString() == "true")
			{
				info.setTransition(true);
			}
		}

		tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(downLeftPosition);
		tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
		if(tileGID)
		{
			ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();

			if(flags.at("Right").asString() == "true")
			{
				 if(currentStatusDescription == FALL_LEFT_ID ||
					currentStatusDescription == JUMP_LEFT_ID ||
					currentStatusDescription == WALK_LEFT_ID ||
					currentStatusDescription == STAND_RIGHT_ID ||
					currentStatusDescription == STAND_LEFT_ID)
				{
					info.setRightCollision(true);
				}
			}

			if(flags.at("Transition").asString() == "true")
			{
				info.setTransition(true);
			}
		}
    }

	tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(leftPosition);
	tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
	if(tileGID)
	{
		ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();

		if(flags.at("Right").asString() == "true")
		{
			 if(currentStatusDescription == FALL_LEFT_ID ||
				currentStatusDescription == JUMP_LEFT_ID ||
				currentStatusDescription == WALK_LEFT_ID ||
				currentStatusDescription == STAND_RIGHT_ID ||
				currentStatusDescription == STAND_LEFT_ID)
			{
				info.setRightCollision(true);
			}
		}

		if(flags.at("Transition").asString() == "true")
		{
			info.setTransition(true);
		}
	}

	tilePosition = CollisionHandler::_levelback->getTileNumberByPosition(upPosition);
    tileGID = CollisionHandler::_layer->getTileGIDAt(tilePosition);
	if(tileGID)
    {
		ValueMap flags = CollisionHandler::_levelback->getPropertiesForGID(tileGID).asValueMap();
        if(flags.at("Down").asString() == "true")
        {
            if(currentStatusDescription == JUMP_LEFT_ID ||
               currentStatusDescription == JUMP_RIGHT_ID)
            {
                info.setDownCollision(true);
            }
        }
		
		if(flags.at("Transition").asString() == "true")
		{
			info.setTransition(true);
		}
	}
	/*** FIN COLISION A DERECHA DEL TILE ***/
}


void CollisionHandler::setMetaLayer(TMXLayer* metaLayer)
{
    CollisionHandler::_layer = metaLayer;
}

void CollisionHandler::setLevelBackground(LevelBackground* background)
{
    CollisionHandler::_levelback = background;
}
