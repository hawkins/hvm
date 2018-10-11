/*
 * =====================================================================================
 *
 *       Filename:  hvm.c
 *
 *    Description:  An exercise in writing a virtual machine in C
 *
 *        Version:  1.0
 *        Created:  10/10/2018 21:47:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Josh Hawkins <hawkins@users.noreply.github.com>
 *
 * =====================================================================================
 */
#include <stdio.h>

// TODO: How can I utilize 0,1,2,3,4?
typedef enum { PUSH, POP, ADD, SET, HALT } InstructionSet;

typedef enum { A, B, C, D, E, F, SP, IP, NUM_OF_REGISTERS } Registers;
int registers[NUM_OF_REGISTERS];

#define stack_pointer (registers[SP])
#define instruction_pointer (registers[IP])

// TODO: Example program, hardcoded for now
const int program[] = {PUSH, 5,  PUSH, 6,   ADD, PUSH, 7,
                       PUSH, 14, ADD,  ADD, POP, HALT};

// Global state
int stack[256];

int fetch() { return program[++instruction_pointer]; }
int pop() { return stack[stack_pointer--]; }
void push(int immediate) { stack[++stack_pointer] = immediate; }

int running = 1;

void eval(int instr) {
  switch (instr) {
    case PUSH: {
      push(fetch());
      break;
    }
    case POP: {
      int val = pop();
      printf("%i\n", val);
      break;
    }
    case ADD: {
      int a = pop();
      int b = pop();
      push(a + b);
      break;
    }
    case SET: {
      int reg = fetch();
      int val = fetch();
      registers[reg] = val;
      break;
    }
    case HALT:
    default: {
      running = 0;
      break;
    }
  }
}

int main() {
  instruction_pointer = -1;
  while (running) {
    int instruction = fetch();
    eval(instruction);
  }

  return 0;
}
