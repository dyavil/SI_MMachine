#include "player.hpp"

#include <SDL2/SDL.h>

Player::Player() : 
  terrain_(nullptr),
  forward_(false),
  backward_(true),
  switchable_(true),
  controller_(nullptr),
  active_(false),
  speed_(0.f, 0.f, 0.f),
  last_time_(0),
  position_(0.f, 0.f, 0.f),
  direction_(1.f, 0.f, 0.f),
  normal_(0.f, 0.f, 0.f),
  //useful parameters to control the movement behavior
  acceleration_(0.0004f),
  turning_angle_(3.f),
  max_speed_(7.f),
  friction_(0.02f, 0.1f) //front and lateral friction for drift
{}

void Player::spawn_at(const Point& position, const Vector& direction, const Point pmin, const Point pmax) {
  //reset position on terrain
  position_ = position ;
  direction_ = direction ;
  float widthR = (pmax.x - pmin.x)/2.0;
  float highR = (pmax.y - pmin.y)/2.0;
  cbox = CollideBox(Point(position_.x - widthR, position_.y - highR, position_.z), Point(position_.x + widthR, position_.y + highR, position_.z));
  project(position_) ;

  //reset speed
  speed_ = Vector(0.f, 0.f, 0.f) ;

  //wait for activation
  deactivate() ;
}

void Player::step(Brick & brick) {
  //do not move if inactive
  if(!active_) return ;

  //handle friction
  Vector linear = dot(speed_, direction_)*direction_ ;
  Vector lateral = speed_ - linear ;
  Vector realdir = normalize(linear);
  speed_ = speed_ - friction_.x * linear ;
  speed_ = speed_ - friction_.y * lateral ;

  //backward or forward
  if(forward_) {
    //handle accelerations
    if(controller_->up()) {
      speed_ = speed_ + direction_ * acceleration_ ;
    }

    if(controller_->down()) {
      speed_ = speed_ - direction_ * acceleration_ ;
      if(dot(speed_, direction_) < 0) {
        speed_ = Vector(0.f, 0.f, 0.f) ;
      }
    }

    //handle rotation
    if(controller_->left()) {
      direction_ = Rotation(normal_, turning_angle_)(direction_) ;
    }
    if(controller_->right()) {
      direction_ = Rotation(normal_, -turning_angle_)(direction_) ;
    }
  } else {
    //handle accelerations
    if(controller_->up()) {
      speed_ = speed_ + direction_ * acceleration_ ;
      if(dot(speed_, direction_) > 0) {
        speed_ = Vector(0.f, 0.f, 0.f) ;
      }
    }

    if(controller_->down()) {
      speed_ = speed_ - direction_ * acceleration_ ;
    }

    //handle rotation
    if(controller_->left()) {
      direction_ = Rotation(normal_, -turning_angle_)(direction_) ;
    }
    if(controller_->right()) {
      direction_ = Rotation(normal_, turning_angle_)(direction_) ;
    }
  }

  //handle the switch breaking // moving backwards
  //control needs to be released then pushed again
  if(length(speed_) == 0.f) {
    if(switchable_) {
      if(controller_->down()) {
        forward_ = false ;
        backward_ =true;
      } 
      if(controller_->up()) {
        forward_ = true ;
        backward_ =false;
      }
    }
  }

  switchable_ = !(
      controller_->up() 
      || controller_->down() 
      || controller_->left() 
      || controller_->right()
      ) ;

  //compute new position position
  int time = SDL_GetTicks() ;
  Point new_position = position_ + (time - last_time_) * speed_ ;


  CollideBox temp = cbox;
  temp.update((time - last_time_) * speed_);
  Vector r = ((time - last_time_) * speed_);
  
  if (int col = brick.collideSide(temp))
  {
    //TODO : don't stop, just slow it down
    //down speed
    //std::cout <<  " collide "<< std::endl;
    speed_ = direction_ * acceleration_ ;
    if(col > 0){
		Vector v = ((time - last_time_) * speed_);
    std::cout << direction_ << ", " << forward_ << std::endl;
		switch (col)
		{
		case 1:
			if (forward_) r = -2 * dot(v, Vector(0, 2, 0))*Vector(0, 2, 0) - v;
			else if(backward_) r = 2 * dot(v, Vector(0, 2, 0))*Vector(0, 2, 0) - v;
      std::cout <<  " collide 1"<< std::endl;
			break;
		case 2 :
			if (forward_) r = -2 * dot(v, Vector(2, 0, 0))*Vector(2, 0, 0) - v;
			else if(backward_) r = 2 * dot(v, Vector(2, 0, 0))*Vector(2, 0, 0) - v;
      std::cout <<  " collide 2"<< std::endl;
			break;
		case 3:
			if (forward_) r = -2 * dot(v, Vector(0, -2, 0))*Vector(0, -2, 0) - v;
			else if(backward_) r = 2 * dot(v, Vector(0, -2, 0))*Vector(0, -2, 0) - v;
      std::cout <<  " collide 3"<< std::endl;
			break;
		case 4:
			if (forward_){
        r = -2 * dot(v, Vector(-2, 0, 0))*Vector(-2, 0, 0) - v;
        std::cout <<  " collide 41 "<< std::endl;
      }
			else if(backward_) {
        r = 2 * dot(v, Vector(-2, 0, 0))*Vector(-2, 0, 0) - v;
          std::cout <<  " collide 42, " << std::endl;
        }
			break;
		default:
			break;
		}
        
        new_position = position_ + r;
        cbox.update(r);
        project(new_position) ;
        //update speed taking projection into account
        speed_ = (new_position - position_) / (time - last_time_) ;
        speed_ = speed_ - dot(speed_, normal_)*normal_ ;

        //update the position
        position_ = new_position ;

    }
    
  }
  else{
    //cbox
    cbox.update(r);

    //project
    project(new_position) ;

    //update speed taking projection into account
    speed_ = (new_position - position_) / (time - last_time_) ;
    speed_ = speed_ - dot(speed_, normal_)*normal_ ;

    //update the position
    position_ = new_position ;
  }

  //update time
  last_time_ = time ;
}

void Player::collideOther(CollideBox & colbox) {
	if (cbox.collide(colbox)) {
		if (forward_) speed_ = -direction_ * acceleration_;
		else speed_ = direction_ * acceleration_;
	}
}

bool Player :: active() {
  return active_ ;
}

void Player::activate() {
  active_ = true ;
}

void Player::deactivate() {
  active_ = false ;
}

Transform Player::transform(Brick & brick) {
  step(brick) ;
  return Transform(direction_, cross(normal_, direction_), normal_, position_ - Point()) ;
}

void Player::set_terrain(const Terrain* terrain) {
  terrain_ = terrain ;
}

void Player::set_controller(const Controller* controller) {
  controller_ = controller ;
}

void Player::project(Point& candidate) {
  //project position and get normal
  terrain_->project(position_, candidate, normal_) ;

  //project direction
  direction_ = normalize(direction_ - dot(direction_, normal_)*normal_) ;
}
