# C-Board-Game
A C application simulating a board game using discrete structures, set theory, and logic given a list of specifications.

## Specifications
### Applicable Sets
• **A** : {*x* ∈ Z<sup>+</sup> | *x* ≤ 4}</br>
• **P** : **A** × **A**</br>
• **B** : {true, false}</br>
• **W** : {{(1, 4), (2, 4), (3, 4)}, {(2, 2), (3, 3), (4, 4)}, {(2, 3), (3, 2), (4, 1)}, {(4, 2), (4, 3), (4, 4)}}</br>
• **H** : {(1, 1), (1, 2), (1, 3), (2, 1), (3, 1)}</br>

### System Variables
• **Ord, Cha, Free** ⊆ **P**</br>
• *turn* ∈ **B**</br>
• *over* ∈ **B**</br>

### System Facts
• **Free** = **P** − (**Ord** ∪ **Cha**)</br>
• *over* ↔ (**Cha** ∈ **W** ∨ **Free** − **H** = ∅)</br>

### System Initialization
• *turn* = true</br>
• **Ord** = ∅</br>
• **Cha** = ∅</br>

### System States and Behavior
**NextPlayerMove** (*pos* ∈ **P**)</br>
  &emsp; &emsp; &emsp; (*turn* ∧ *pos* 6 ∈ **H** ∧ *pos* ∈ **Free**)&emsp; → &emsp; **Cha** = **Cha** ∪ {*pos*}</br>
  &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; ∧ *turn* = ¬*turn*</br>
  &emsp; &emsp; &emsp; (¬*turn* ∧ *pos* ∈ **Free** ∧ |**Ord**| < 4)&emsp;→&emsp;**Ord** = **Ord** ∪ {*pos*}</br>
  &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp;  ∧ *turn* = ¬*turn*</br>
  &emsp; &emsp; &emsp; (¬*turn* ∧ |**Ord**| = 4 ∧ *pos* ∈ **Ord**)&emsp;→&emsp;**Ord** = **Ord** − {*pos*}</br>
  
**GameOver** (over)</br>
&emsp; &emsp; &emsp; *result* &emsp;∈&emsp;{Ord wins, Cha wins}</br>
&emsp; &emsp; &emsp; **Cha** ∈ **W** &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp;&emsp;   →&emsp;*result* = Cha Wins</br>
&emsp; &emsp; &emsp; **Free** − **H** = ∅&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; → &emsp; *result* = Ord Wins</br>

<h2>💌 Credits ✉️</h2>
This project is done by <b>FURIGAY, Ralph Angelo, ERMITANO, Kate Justine</b> and <b>KAWACHI, Ron Hideki</b> as a requirement to pass CCDSTRU under the instructions of <b>Dr Shirley Chu</b>, submitted on May 24, 2021.
