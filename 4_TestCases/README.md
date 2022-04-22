## TEST PLAN AND OUTPUTS

# Test Plans

| **Test ID** | **Description** | **Input** | **Output** | **Status** |
| --- | --- | --- | --- | --- |
| TID\_01 | Motor control | input = 1 | 4 motor moves backwards  | PASS |
| TID\_02 | Motor control | input = 2 | Right turn of motor  | PASS |
| TID\_03 | Motor control | input = 3 | Left turn of motor  | PASS |
| TID\_04 | Motor control | input = 4 | Forward movement of motor  | PASS |
| TID\_05 | Motor control | input = except given set | Turn motor OFF  | PASS |
| TID\_01 | Distance control | input <= 16 | Obstalce detected | PASS |
| TID\_06 | Distance Control | input > 16 | No obstacle detected | PASS |


