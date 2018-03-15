 /*
  *  Project     Base 2 to base 8,10 and 16
  *  @author     Hamza Jadid
  *  @license    MIT - Copyright (c) 2018 Hamza Jadid
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  *
 */

#include<Keyboard.h>
#define ONE 3
#define ZERO 4
#define ENTER 5

typedef struct binary {
	int data;
	struct binary * next;
} binary;

binary * head = NULL;
binary * oct = NULL;
binary * hex = NULL;

void Push(binary ** headRef, int d) {
	binary * newBinary = (binary*)malloc(sizeof(binary));
	newBinary->data = d;
	newBinary->next = *headRef;
	*headRef = newBinary;
}

void biToDec(binary * head) {
	unsigned int sum = 0;
	if (!head)
		return;
	for (int i = 0; head; i++, head = head->next)
		sum += head->data * (int)(pow(2, i) + 0.5);
	Keyboard.print("\nBase 10: ");
	Keyboard.print(sum);
	return;
}

void biToOct(binary * head) {
	int sum = 0;
	if (!head)
		return;
	for (int i = 0; head && i < 3; i++, head = head->next)
		sum += head->data * (int)(pow(2, i) + 0.5);
	Push(&oct, sum);
	biToOct(head);
}

void biToHex(binary * head) {
	int sum = 0;
	if (!head)
		return;
	for (int i = 0; head && i < 4; i++, head = head->next)
		sum += head->data * (int)(pow(2, i) + 0.5);
	Push(&hex, sum);
	biToHex(head);
}

void printList(binary * head) {
	if (!head)
		Keyboard.print("null");
	for (; head; head = head->next) {
		switch (head->data)
		{
		case 10: Keyboard.print("A"); break;
		case 11: Keyboard.print("B"); break;
		case 12: Keyboard.print("C"); break;
		case 13: Keyboard.print("D"); break;
		case 14: Keyboard.print("E"); break;
		case 15: Keyboard.print("F"); break;
		default: Keyboard.print(head->data); break;
		}
	}
}

void calculateAll(){
  biToDec(head);
  biToOct(head);
  biToHex(head);
}

void printAll(){
  Keyboard.print("\nBase 8: ");
  printList(oct);
  Keyboard.print("\nBase 16: ");
  printList(hex);
  Keyboard.print("\n\nEnter a base 2 number: ");
}

void erase(binary ** headRef) {
	free(*headRef);
	*headRef = NULL;
}

void eraseAll(){
  erase(&head);
  erase(&oct);
  erase(&hex);
}

void driver(){
  Keyboard.begin();
  if (!digitalRead(ONE))
  {
    Keyboard.write('1');
    Push(&head,1);
    delay(700);
  }
  else if (!digitalRead(ZERO)){
    Keyboard.write('0');
    Push(&head,0);
    delay(700);
}
  else if (!digitalRead(ENTER)){
    calculateAll();
    printAll();
    eraseAll();
    delay(700);
  }
  Keyboard.end();
}

void setup() {
  pinMode(ZERO,INPUT_PULLUP);
  pinMode(ONE,INPUT_PULLUP);
  pinMode(ENTER,INPUT_PULLUP);
}

void loop() {
  driver();
}
