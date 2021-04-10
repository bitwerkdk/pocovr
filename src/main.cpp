#include <Arduino.h>
#include "./gfx/gfx.h"
#include "./math/math.h"
#include "./objects/scene.h"
#include "./physics/time.h"
#include "./state/state.h"

objects::scene mainScene(5, 40);

void createScene() {
  // Make lights
  mainScene.lights.push_back(objects::light(math::vector3F(FX_FROM_F(2), FX_FROM_F(1), FX_FROM_F(-1)), FX_FROM_F(1)));
  mainScene.lights.push_back(objects::light(math::vector3F(FX_FROM_F(-2), FX_FROM_F(1), FX_FROM_F(-1)), FX_FROM_F(0.5)));

  // Make room
  /*const math::fixed left = FX_FROM_F(-4);
  const math::fixed right = FX_FROM_F(4);
  const math::fixed down = FX_FROM_F(-2);
  const math::fixed up = FX_FROM_F(3);
  const math::fixed back = FX_FROM_F(-4);
  const math::fixed front = FX_FROM_F(4);
  objects::mesh* room = new objects::mesh(math::vector3F(0, 0, 0));
  room->tris.push_back(objects::tri(math::vector3F(left, down, back), math::vector3F(left, up, back), math::vector3F(left, up, front)));
  room->tris.push_back(objects::tri(math::vector3F(left, down, back), math::vector3F(left, up, front), math::vector3F(left, down, front)));
  room->tris.push_back(objects::tri(math::vector3F(right, down, front), math::vector3F(right, up, front), math::vector3F(right, up, back)));
  room->tris.push_back(objects::tri(math::vector3F(right, down, front), math::vector3F(right, up, back), math::vector3F(right, down, back)));
  room->tris.push_back(objects::tri(math::vector3F(left, down, back), math::vector3F(left, down, front), math::vector3F(right, down, front)));
  room->tris.push_back(objects::tri(math::vector3F(left, down, back), math::vector3F(right, down, front), math::vector3F(right, down, back)));
  room->tris.push_back(objects::tri(math::vector3F(left, up, front), math::vector3F(left, up, back), math::vector3F(right, up, back)));
  room->tris.push_back(objects::tri(math::vector3F(left, up, front), math::vector3F(right, up, back), math::vector3F(right, up, front)));
  room->tris.push_back(objects::tri(math::vector3F(right, down, back), math::vector3F(right, up, back), math::vector3F(left, up, back)));
  room->tris.push_back(objects::tri(math::vector3F(right, down, back), math::vector3F(left, up, back), math::vector3F(left, down, back)));
  room->tris.push_back(objects::tri(math::vector3F(left, down, front), math::vector3F(left, up, front), math::vector3F(right, up, front)));
  room->tris.push_back(objects::tri(math::vector3F(left, down, front), math::vector3F(right, up, front), math::vector3F(right, down, front)));
  mainScene.meshes.push_back(room);*/

  // Make pyramid
  objects::mesh* pyramid = new objects::mesh(math::vector3F(FX_FROM_F(1), FX_FROM_F(2.5), FX_FROM_F(3)));
  pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(1))));
  pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(1), FX_FROM_F(-1), FX_FROM_F(-1))));
  pyramid->tris.push_back(objects::tri(math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(1)), math::vector3F(FX_FROM_F(0), FX_FROM_F(1), FX_FROM_F(0)), math::vector3F(FX_FROM_F(-1), FX_FROM_F(-1), FX_FROM_F(-1))));
  mainScene.meshes.push_back(pyramid);
}

void setup() {
  Serial.begin(115200);

  createScene();

  //state::setup();
  gfx::initialize();
}

void loop() {
  mainScene.meshes[0]->objTransform.rotateY(FX_MUL(FX_FROM_F(90), physics::deltaTimeSec));
  //gfx::headsetTransform.pos.z -= physics::deltaTimeSec;

  gfx::renderScene(mainScene);
  
  physics::updateTime();
}