
// A stack class for characters. 
package sdemo;
/**
 *
 * @author User
 */
public class Stack {  
  private char stck[]; // this array holds the stack 
  private int tos;  // top of stack 
  
  // Construct an empty Stack given its size. 
  Stack(int size) {  
    stck = new char[size]; // allocate memory for stack 
    tos = 0;  
  }  
 
  // Construct a Stack from a Stack. 
  Stack(Stack ob) { 
    tos = ob.tos; 
    stck = new char[ob.stck.length]; 
 
    // copy elements 
    for(int i=0; i < tos; i++) 
      stck[i] = ob.stck[i]; 
  } 
 
  // Construct a stack with initial values. 
  Stack(char a[]) { 
    stck = new char[a.length]; 
 
    for(int i = 0; i < a.length; i++) { 
      push(a[i]); 
    }     
  } 
 
    
  // Push characters onto the stack. 
  void push(char ch) {  
    if(tos==stck.length) {  
      System.out.println(" -- Stack is full.");  
      return;  
    }  
      
    stck[tos] = ch; 
    tos++; 
  }  
  
  // Pop a character from the stack. 
  char pop() {  
    if(tos==0) {  
      System.out.println(" -- Stack is empty.");  
      return (char) 0;   
    }  
    
    tos--;  
    return stck[tos];  
  }  
}  
  