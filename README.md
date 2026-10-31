# Theory of Computation Lab Experiments (CSA13)

**Institution:** Saveetha School of Engineering, SIMATS  
**Department:** Department of Computer Science and Engineering  
**Course Code:** CSA13  
**Course Name:** Theory of Computation  

This repository contains C source code implementations and JFLAP simulator models for Experiments 1 through 17 of the Theory of Computation laboratory curriculum.

---

## 📚 Experiments Index

| Exp No. | File Name | Description | Topic |
|---|---|---|---|
| **01** | [`01_dfa_start_end_a.c`](01_dfa_start_end_a.c) | DFA simulating strings starting with `'a'` and ending with `'a'` | DFA |
| **02** | [`02_dfa_start_0_end_1.c`](02_dfa_start_0_end_1.c) | DFA simulating strings starting with `'0'` and ending with `'1'` | DFA |
| **03** | [`03_cfg_0A1.c`](03_cfg_0A1.c) | Check string membership for CFG: $S \to 0A1, A \to 0A \mid 1A \mid \varepsilon$ | CFG |
| **04** | [`04_cfg_palindrome.c`](04_cfg_palindrome.c) | Check string membership for CFG: $S \to 0S0 \mid 1S1 \mid 0 \mid 1 \mid \varepsilon$ (Palindromes) | CFG |
| **05** | [`05_cfg_0S0_A.c`](05_cfg_0S0_A.c) | Check string membership for CFG: $S \to 0S0 \mid A, A \to 1A \mid \varepsilon$ ($0^n 1^m 0^n$) | CFG |
| **06** | [`06_cfg_0S1.c`](06_cfg_0S1.c) | Check string membership for CFG: $S \to 0S1 \mid \varepsilon$ ($0^n 1^n$) | CFG |
| **07** | [`07_cfg_substring_101.c`](07_cfg_substring_101.c) | Check string membership for CFG: $S \to A101A, A \to 0A \mid 1A \mid \varepsilon$ (Substring `"101"`) | CFG |
| **08** | [`08_nfa_start_b_end_a.c`](08_nfa_start_b_end_a.c) | NFA simulation for strings starting with `'b'` and ending with `'a'` | NFA |
| **09** | [`09_nfa_start_0_end_1.c`](09_nfa_start_0_end_1.c) | NFA simulation for strings starting with `'0'` and ending with `'1'` | NFA |
| **10** | [`10_nfa_epsilon_closure.c`](10_nfa_epsilon_closure.c) | Computation of $\varepsilon$-closure for all states in an $\varepsilon$-NFA | $\varepsilon$-NFA |
| **11** | [`11_epsilon_nfa_to_dfa.c`](11_epsilon_nfa_to_dfa.c) | $\varepsilon$-closure calculation & Subset Construction to convert $\varepsilon$-NFA to DFA | Conversion |
| **12** | [`12_dfa_simulator_strings.c`](12_dfa_simulator_strings.c) | DFA simulator accepting input strings `"a"`, `"ac"`, and `"bac"` | DFA Simulator |
| **13** | [`13_pda_simulator_aabb.c`](13_pda_simulator_aabb.c) | PDA simulator accepting input string `"aabb"` ($a^n b^n$) | PDA Simulator |
| **14** | [`14_pda_simulator_an_b2n.c`](14_pda_simulator_an_b2n.c) | PDA simulator accepting input strings $a^n b^{2n}$ ($n \ge 1$) | PDA Simulator |
| **15** | [`15_tm_simulator_an_bn.c`](15_tm_simulator_an_bn.c) | Turing Machine simulator accepting input strings $a^n b^n$ ($n \ge 1$) | TM Simulator |
| **16** | [`16_tm_simulator_an_b2n.c`](16_tm_simulator_an_b2n.c) | Turing Machine simulator accepting input strings $a^n b^{2n}$ ($n \ge 1$) | TM Simulator |
| **17** | [`17_tm_simulator_palindrome.c`](17_tm_simulator_palindrome.c) | Turing Machine simulator accepting Palindrome string `"ababa"` | TM Simulator |

---

## 🛠️ Compilation and Execution

### Prerequisites
- A C compiler (`gcc` or `clang`)
- `make` utility

### Compile All Programs
To compile all 17 experiments in one command:
```bash
make
```

### Run an Individual Program
```bash
./01_dfa_start_end_a
./02_dfa_start_0_end_1
./03_cfg_0A1
# ... and so forth
```

### Clean Binaries
To remove compiled executables:
```bash
make clean
```

---

## 🖥️ JFLAP Simulator Models (`simulators/`)

For experiments 12 through 17 which specify designing automata using simulators, matching JFLAP `.jff` models are included in the [`simulators/`](simulators/) directory:

- [`simulators/12_dfa_a_ac_bac.jff`](simulators/12_dfa_a_ac_bac.jff): DFA accepting `{"a", "ac", "bac"}`
- [`simulators/13_pda_aabb.jff`](simulators/13_pda_aabb.jff): Pushdown Automata accepting `aabb`
- [`simulators/14_pda_an_b2n.jff`](simulators/14_pda_an_b2n.jff): Pushdown Automata accepting $a^n b^{2n}$
- [`simulators/15_tm_an_bn.jff`](simulators/15_tm_an_bn.jff): Turing Machine accepting $a^n b^n$
- [`simulators/16_tm_an_b2n.jff`](simulators/16_tm_an_b2n.jff): Turing Machine accepting $a^n b^{2n}$
- [`simulators/17_tm_palindrome_ababa.jff`](simulators/17_tm_palindrome_ababa.jff): Turing Machine accepting Palindromes (`ababa`)

These files can be opened and simulated directly in **JFLAP 7.x** or simulated using the included C programs.

---

## 🔬 Experiment Details & Transition Highlights

### 1. DFA: Strings starting and ending with `'a'`
- **Alphabet:** $\Sigma = \{a, b\}$
- **States:** $q_0$ (Start), $q_1$ (Accepting), $q_2$, $q_{\text{trap}}$
- $\delta(q_0, a) = q_1, \delta(q_0, b) = q_{\text{trap}}$
- $\delta(q_1, a) = q_1, \delta(q_1, b) = q_2$
- $\delta(q_2, a) = q_1, \delta(q_2, b) = q_2$

### 2. DFA: Strings starting with `'0'` and ending with `'1'`
- **Alphabet:** $\Sigma = \{0, 1\}$
- **States:** $q_0$ (Start), $q_1$, $q_2$ (Accepting), $q_{\text{trap}}$
- $\delta(q_0, 0) = q_1, \delta(q_0, 1) = q_{\text{trap}}$
- $\delta(q_1, 0) = q_1, \delta(q_1, 1) = q_2$
- $\delta(q_2, 0) = q_1, \delta(q_2, 1) = q_2$

### 3. CFG: $S \to 0A1, A \to 0A \mid 1A \mid \varepsilon$
- Generates strings of length $\ge 2$ that start with `0` and end with `1` with any binary sequence in between.
- Validates the string and prints the leftmost derivation step by step.

### 4. CFG: $S \to 0S0 \mid 1S1 \mid 0 \mid 1 \mid \varepsilon$
- Generates the set of all Palindromes over $\{0, 1\}$ (both even and odd lengths).

### 5. CFG: $S \to 0S0 \mid A, A \to 1A \mid \varepsilon$
- Language: $L = \{ 0^n 1^m 0^n \mid n \ge 0, m \ge 0 \}$.
- Checks equal count of leading and trailing zeros with contiguous ones in between.

### 6. CFG: $S \to 0S1 \mid \varepsilon$
- Language: $L = \{ 0^n 1^n \mid n \ge 0 \}$.
- Verifies exact matching counts of `0`s followed by equal count of `1`s.

### 7. CFG: $S \to A101A, A \to 0A \mid 1A \mid \varepsilon$
- Language: Any binary string containing `"101"` as a substring.
- Locates the substring and derives the prefix and suffix via non-terminal $A$.

### 8. NFA: Strings starting with `'b'` and ending with `'a'`
- Non-deterministic state branching on `'a'`: $\delta(q_1, a) = \{q_1, q_2\}$.
- Tracks the active state subset dynamically at each step.

### 9. NFA: Strings starting with `'0'` and ending with `'1'`
- Non-deterministic branching on `'1'`: $\delta(q_1, 1) = \{q_1, q_2\}$.

### 10. $\varepsilon$-Closure of States
- Finds $\varepsilon\text{-closure}(q)$ for every state $q$ in an $\varepsilon$-NFA using Depth-First Search (DFS) / Transitive Closure.

### 11. $\varepsilon$-NFA to DFA Conversion
- Computes $\varepsilon$-closure of state subsets.
- Constructs equivalent DFA transition table using Subset Construction.
- Simulates test strings on the resulting DFA.

### 12. DFA Simulator for `{"a", "ac", "bac"}`
- Minimal DFA over $\{a, b, c\}$ accepting only the 3 designated words and rejecting all others.

### 13. PDA Simulator: String `"aabb"`
- Demonstrates instantaneous configuration transitions:
  $$(q_0, aabb, Z_0) \vdash (q_0, abb, AZ_0) \vdash (q_0, bb, AAZ_0) \vdash (q_1, b, AZ_0) \vdash (q_1, \varepsilon, Z_0) \vdash (q_2, \varepsilon, Z_0) \quad [\text{ACCEPT}]$$

### 14. PDA Simulator: $a^n b^{2n}$ ($n \ge 1$)
- Pushes TWO stack symbols for every `'a'`.
- Pops ONE stack symbol for every `'b'`.

### 15. Turing Machine: $a^n b^n$ ($n \ge 1$)
- Step-by-step interactive tape visualization with head positioning marker.
- Replaces `'a'` with `'X'`, moves right to find matching `'b'`, marks with `'Y'`, returns left to next `'a'`.

### 16. Turing Machine: $a^n b^{2n}$ ($n \ge 1$)
- Replaces each `'a'` with `'X'` and pairs it with TWO `'b'`s marked as `'Y'`.

### 17. Turing Machine: Palindrome `"ababa"`
- Erases leftmost symbol, scans right to match and erase corresponding rightmost symbol.
- Verifies odd/even palindromes on the tape and halts in accepting state $q_{\text{accept}}$.
