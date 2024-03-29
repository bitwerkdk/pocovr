#include <Arduino.h>
#include "./gfx/gfx.h"
#include "./math/math.h"
#include "./objects/scene.h"
#include "./physics/time.h"
#include "./state/state.h"

objects::scene mainScene(5, 40);

/// Fill mainScene with objects and lights
void createScene() {
  // Make lights
  mainScene.lights.push_back(objects::light(math::vector3FX(FX_FROM_F(2), FX_FROM_F(1), FX_FROM_F(-1)), FX_FROM_F(1)));
  mainScene.lights.push_back(objects::light(math::vector3FX(FX_FROM_F(-2), FX_FROM_F(1), FX_FROM_F(-1)), FX_FROM_F(0.5)));

  // Make room
  /*const math::fixed left = FX_FROM_F(-4);
  const math::fixed right = FX_FROM_F(4);
  const math::fixed down = FX_FROM_F(-2);
  const math::fixed up = FX_FROM_F(3);
  const math::fixed back = FX_FROM_F(-4);
  const math::fixed front = FX_FROM_F(4);
  objects::mesh* room = new objects::mesh(math::vector3FX(0, 0, 0));
  room->tris.push_back(objects::tri(math::vector3FX(left, down, back), math::vector3FX(left, up, back), math::vector3FX(left, up, front)));
  room->tris.push_back(objects::tri(math::vector3FX(left, down, back), math::vector3FX(left, up, front), math::vector3FX(left, down, front)));
  room->tris.push_back(objects::tri(math::vector3FX(right, down, front), math::vector3FX(right, up, front), math::vector3FX(right, up, back)));
  room->tris.push_back(objects::tri(math::vector3FX(right, down, front), math::vector3FX(right, up, back), math::vector3FX(right, down, back)));
  room->tris.push_back(objects::tri(math::vector3FX(left, down, back), math::vector3FX(left, down, front), math::vector3FX(right, down, front)));
  room->tris.push_back(objects::tri(math::vector3FX(left, down, back), math::vector3FX(right, down, front), math::vector3FX(right, down, back)));
  room->tris.push_back(objects::tri(math::vector3FX(left, up, front), math::vector3FX(left, up, back), math::vector3FX(right, up, back)));
  room->tris.push_back(objects::tri(math::vector3FX(left, up, front), math::vector3FX(right, up, back), math::vector3FX(right, up, front)));
  room->tris.push_back(objects::tri(math::vector3FX(right, down, back), math::vector3FX(right, up, back), math::vector3FX(left, up, back)));
  room->tris.push_back(objects::tri(math::vector3FX(right, down, back), math::vector3FX(left, up, back), math::vector3FX(left, down, back)));
  room->tris.push_back(objects::tri(math::vector3FX(left, down, front), math::vector3FX(left, up, front), math::vector3FX(right, up, front)));
  room->tris.push_back(objects::tri(math::vector3FX(left, down, front), math::vector3FX(right, up, front), math::vector3FX(right, down, front)));
  mainScene.meshes.push_back(room);*/

  // Make pyramid
  objects::mesh* pyramid = new objects::mesh(math::vector3FX(FX_FROM_F(0), FX_FROM_F(0), FX_FROM_F(3)));
  pyramid->tris.push_back(objects::tri(math::vector3FX(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3FX(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3FX(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3FX(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3FX(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3FX(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3FX(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3FX(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3FX(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3FX(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3FX(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3FX(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3FX(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3FX(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3FX(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1))));
  pyramid->tris.push_back(objects::tri(math::vector3FX(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3FX(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3FX(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1))));
  mainScene.meshes.push_back(pyramid);
}

void setup() {
  Serial.begin(115200);

  createScene();

  //state::setup();
  gfx::initialize();

  // Potentiometers
  pinMode(26, INPUT);
  pinMode(27, INPUT);

  mainScene.meshes[0]->objTransform.rotate(math::vector3FX::up(), 45);
}

void loop() {
  //mainScene.meshes[0]->objTransform.rotate((math::vector3FX::up() + math::vector3FX::right()).normalized(), 90 * FX_TO_F(physics::deltaTimeSec));
  mainScene.meshes[0]->objTransform.rotate(math::vector3FX::right(), 90 * FX_TO_F(physics::deltaTimeSec));

  gfx::renderScene(mainScene);
  
  physics::updateTime();

  // Potentiometers
  //gfx::screenOffset = math::fxLerp(-16, 16, FX_FROM_I(analogRead(26)) / 4096);
  //gfx::headsetTransform.pos.z = math::fxLerp(FX_FROM_F(-1), FX_FROM_F(1), FX_FROM_I(analogRead(27)) / 4096);
}