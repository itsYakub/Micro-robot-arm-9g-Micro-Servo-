#include <MobaTools.h>

enum e_stateMachine {
  STATE_NONE = 0,
  STATE_ROTATE_LEFT,
  STATE_ROTATE_RIGHT,
  STATE_SHAKE_HEAD,

  /* ... */

  STATE_COUNT
};

int main(void) {
  /* initialize arduino platform... */
  init();
  Serial.begin(115200);

  /* intialize servos... */

  MoToServo s_foot;
  s_foot.attach(8);
  s_foot.setSpeed(25);
  s_foot.write(90);
  
  MoToServo s_swing;
  s_swing.attach(9);
  s_swing.setSpeed(25);
  s_swing.write(90);
 
  MoToServo s_arm1;
  s_arm1.attach(10);
  s_arm1.setSpeed(25);
  s_arm1.write(0);
 
  MoToServo s_arm2;
  s_arm2.attach(11);
  s_arm2.setSpeed(25);
  s_arm2.write(45);
  
  MoToServo s_arm3;
  s_arm3.attach(12);
  s_arm3.setSpeed(25);
  s_arm3.write(90);

  /* initialize state machine... */
  enum e_stateMachine state_machine = STATE_ROTATE_LEFT;

  delay(1000);
  while (1) {
    
    /* update state machine... */

    switch (state_machine) {

      case (STATE_ROTATE_LEFT): {
        s_foot.write(180);
        while (s_foot.moving()) { }

        state_machine = STATE_SHAKE_HEAD;
      } break;
      


      case (STATE_ROTATE_RIGHT): {
        s_foot.write(0);
        while (s_foot.moving()) { }

        state_machine = STATE_SHAKE_HEAD;
      } break;
     


      case (STATE_SHAKE_HEAD): {
        int8_t arm1_angle = s_arm1.read();
        int8_t arm2_angle = s_arm2.read();

        /* perform n-number of head shakes... */
        s_arm1.setSpeed(25); s_arm2.setSpeed(25);
        for (size_t i = 0; i < 3; i++) {
          s_arm1.write(arm1_angle + 45);
          s_arm2.write(arm2_angle - 45);
          while (s_arm1.moving() || s_arm2.moving()) { }
          
          s_arm1.write(arm1_angle);
          s_arm2.write(arm2_angle);
          while (s_arm1.moving() || s_arm2.moving()) { }
        }
        s_arm1.setSpeed(100); s_arm2.setSpeed(100);

        /* start rotating once again... */
        int foot_angle = s_foot.read(); 
        Serial.println(foot_angle);
        if (foot_angle >= 180) {
          state_machine = STATE_ROTATE_RIGHT;
        }

        else if (foot_angle <= 0) {
          state_machine = STATE_ROTATE_LEFT;
        }
      } break;



      default: { } break;
    }

    delay(50);
  }
}
