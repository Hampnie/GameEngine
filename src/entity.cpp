#include "entity.h"
#include "resourceManager.h"

Entity::Entity(FRect rectangle, std::string ID, phys_body_type phys_type, texture_type type, bodyUserData::body_type bData_type, std::shared_ptr<b2World> physWorld)
    : EmptyEntity(rectangle, type, ID),
      phys_type(phys_type),
      bData_type(bData_type),
      physWorld(physWorld)
{
}

void Entity::init()
{
    FRect physRectangle{rectangle.x/PHYS_MULT_FACTOR, rectangle.y/PHYS_MULT_FACTOR, rectangle.width/PHYS_MULT_FACTOR, rectangle.height/PHYS_MULT_FACTOR};
    b2BodyDef physBody;
    physBody.position.Set(physRectangle.x + physRectangle.width/2, physRectangle.y + physRectangle.height/2);
    if( phys_type == phys_body_type::STATIC)
    {               
        body = physWorld->CreateBody(&physBody);

        b2PolygonShape box;
        box.SetAsBox(physRectangle.width/2, physRectangle.height/2);
        body->CreateFixture(&box, 0.0f);

    } else if( phys_type == phys_body_type::DYNAMIC)
    {
        physBody.type = b2_dynamicBody;        
        body = physWorld->CreateBody(&physBody);

        b2PolygonShape box;
        box.SetAsBox(physRectangle.width/2, physRectangle.height/2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &box;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 200.0f;

        body->CreateFixture(&fixtureDef);

        body->SetLinearDamping(1.0f);
    }

    // Set userData for detect collision
    bodyUserData* userData = new bodyUserData;
    userData->type = bData_type;
    userData->self_ptr = this;
    body->SetUserData(userData);
}

