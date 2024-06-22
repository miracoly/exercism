#include <stddef.h>
#include "robot_simulator.h"

static robot_direction_t rotate_right(robot_direction_t direction) {
  return (robot_direction_t) direction + 1 == DIRECTION_MAX ? 0 : direction + 1;
}

static robot_direction_t rotate_left(robot_direction_t direction) {
  return (robot_direction_t) direction == 0 ? DIRECTION_MAX - 1 : direction - 1;
}

static robot_position_t move(robot_direction_t dir, robot_position_t pos) {
  switch (dir) {
    case DIRECTION_NORTH:
      return (robot_position_t) {.x = pos.x, .y = pos.y + 1};
    case DIRECTION_EAST:
      return (robot_position_t) {.x = pos.x + 1, .y = pos.y};
    case DIRECTION_SOUTH:
      return (robot_position_t) {.x = pos.x, .y = pos.y - 1};
    case DIRECTION_WEST:
    case DIRECTION_MAX:
      return (robot_position_t) {.x = pos.x - 1, .y = pos.y};
  }
  return pos;
}

static void execute_command(robot_status_t* robot, char command) {
  switch (command) {
    case 'R':
      robot->direction = rotate_right(robot->direction);
      break;
    case 'L':
      robot->direction = rotate_left(robot->direction);
      break;
    case 'A':
      robot->position = move(robot->direction, robot->position);
    default:
      return;
  }
}

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
  return (robot_status_t) {
    .direction = direction,
    .position = {
      .x = x,
      .y = y,
    }
  };
}

void robot_move(robot_status_t* robot, const char* commands) {
  for(size_t i = 0; commands[i]; ++i) {
    execute_command(robot, commands[i]);
  }
}

