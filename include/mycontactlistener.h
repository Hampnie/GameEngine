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

      //check if fixture A was a bullet
      b2Body* body = contact->GetFixtureA()->GetBody();
      bodyUserData* bud = static_cast<bodyUserData*>(body->GetUserData());
      if(bud)
      {
          if( bud->type == bodyUserData::BT_BULLET)
          {
             Core::instance().deleteEntity(static_cast<Entity*>(bud->self_ptr));
          }
      }

      //check if fixture B was a bullet
      body = contact->GetFixtureB()->GetBody();
      bud = static_cast<bodyUserData*>(body->GetUserData());
      if(bud)
      {
          if( bud->type == bodyUserData::BT_BULLET)
          {
             Core::instance().deleteEntity(static_cast<Entity*>(bud->self_ptr));
          }
      }

    }

    void EndContact(b2Contact* contact)
    {
    }
};

#endif // MYCONTACTLISTENER_H
