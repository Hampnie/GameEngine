#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H
/*
 * Listener class for box2d's collision
 *
 */

#include <Box2D/Box2D.h>
#include "bullet.h"
#include "core.h"

class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {
        std::cout << "Begin contact\n";

      // Body A data
      b2Body* body_A = contact->GetFixtureA()->GetBody();
      bodyUserData* bud_A = static_cast<bodyUserData*>(body_A->GetUserData());
      // body B data
      b2Body* body_B = contact->GetFixtureB()->GetBody();
      bodyUserData* bud_B = static_cast<bodyUserData*>(body_B->GetUserData());

      // Check if it is bullet and player
      if(bud_A && bud_B)
      {
          if( ( (bud_A->type == bodyUserData::BT_BULLET) && (bud_B->type == bodyUserData::BT_PLAYER) ) ||
              ( (bud_B->type == bodyUserData::BT_BULLET) && (bud_A->type == bodyUserData::BT_PLAYER) )  )
          {
             Core::instance().delete_entity(static_cast<EmptyEntity*>(bud_A->self_ptr));
             Core::instance().delete_entity(static_cast<EmptyEntity*>(bud_B->self_ptr));
          }
      }

      // Check if it is bullet and wall

      if( (bud_A->type == bodyUserData::BT_BULLET) && (bud_B->type == bodyUserData::BT_WALL) )
      {
          Core::instance().delete_entity(static_cast<EmptyEntity*>(bud_A->self_ptr));
      }

      if( (bud_B->type == bodyUserData::BT_BULLET) && (bud_A->type == bodyUserData::BT_WALL)) 
      {
          Core::instance().delete_entity(static_cast<EmptyEntity*>(bud_B->self_ptr));
      }


    }

    void EndContact(b2Contact* contact)
    {
    }
};

#endif // MYCONTACTLISTENER_H
