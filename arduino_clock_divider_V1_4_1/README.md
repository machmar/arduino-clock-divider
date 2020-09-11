So here it is. Im actually going throught my modules and fixing them.

This update adds new functionality while still keeping some of the old stuff. 
As in previous versions, plug a cable into the input to select Division mode. Leave the socket empty to select logic mode.
```
Division mode can be further adjusted with the expander (NOT TESTED WITH THIS VERSION) or the jumpers on the back.
Jumpers: 
  prime - 
      unconnected - the module divides by 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
      connected   - the module divides by 1, 2, 3, 5, 7, 11, 13, 17, 19, 23
  serial - !NEVER CONNECT TOGETHER!
  edge - 
      unconnected - the module reacts both to the falling and rising edge of the clock input
      connected   - the module reacts to only the rising edge of the clock input
  g/t -
      unconnected - the module will output a gate signal    - once the division number is reached, the output state will invert
      connected   - the module will output a trigger signal - once the division number is reached, the output state will be set to high to a small ammount of time, after which it will be set back to low
  rst/10 - 
      unconnected - the module will use its "divide by 10" output as a standard output
      connected   - the module will use its "divide by 10" output as a trigger input - when this output recievs a high signal, it will reset all division counters and set all outputs to low
      
Logic mode can not be adjusted with any jumpers - those are exclusive for division mode
  In logic mode, the outputs 1, 2, 9, 10 become inputs and the outputs 3, 4, 5, 6, 7, 8 become outputs of logic operations controlled by the four inputs.
  
  In the code the inputs 1 and 2 are called A and B.
  The output 3 is "A & B" or in other words "both A and B have to be high for the output to be high".
  The output 4 is "A | B" or in other words "either A or B have to be high for the output to be high".
  The output 5 is "A ^ B" or in other words "exclusively only A or only B have to be high for the output to be high".
  
  In the code the inputs 9 and 10 are called C and D.
  The output 3 is "C & D" or in other words "both C and D have to be high for the output to be high".
  The output 4 is "C | D" or in other words "either C or D have to be high for the output to be high".
  The output 5 is "C ^ D" or in other words "exclusively only C or only D have to be high for the output to be high".
  ```

Yeah and thats about it really. I have to say this is a lot of text. It is just explained as clearly as I could. Also this is all written as a code so the dumb GitHub auto formatting doesnt ruin it.

Hope your build comes together well, Marek Mach
