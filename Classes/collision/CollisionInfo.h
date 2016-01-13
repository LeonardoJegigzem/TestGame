#ifndef _COLLISION_INFO_H_
#define _COLLISION_INFO_H_

class CollisionInfo
{
public:

    CollisionInfo(bool up = false, bool down = false, bool left = false, bool right = false, bool transition = false)
    : _leftCollision(left), _rightCollision(right), _upCollision(up), _downCollision(down), _transition(transition){};


    inline void setLeftCollision(bool flag){this->_leftCollision = flag;};
    inline void setRightCollision(bool flag){this->_rightCollision = flag;};
    inline void setUpCollision(bool flag){this->_upCollision = flag;};
    inline void setDownCollision(bool flag){this->_downCollision = flag;};

	inline void setTransition(bool flag){this->_transition = flag;};
		
    inline bool isLeftCollision(){return this->_leftCollision;};
    inline bool isRightCollision(){return this->_rightCollision;};
    inline bool isUpCollision(){return this->_upCollision;};
    inline bool isDownCollision(){return this->_downCollision;};
	
	inline bool isTransition(){return this->_transition;};
private:
    bool _leftCollision;
    bool _rightCollision;
    bool _upCollision;
    bool _downCollision;
	bool _transition;

};

#endif // _COLLISION_INFO_H_
