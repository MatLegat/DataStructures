#pragma once

using namespace std;

/*                      POSIÇÃO DAS PISTAS:
    S1:                 S2:                     SUMIDOUROS:
0 = O1leste         4 = C1leste         8  = O1oeste    11 = N2norte
1 = N1sul           5 = N2sul           9  = N1norte    12 = S2sul
2 = S1norte         6 = S2norte         10 = S1sul      13 = L1leste
3 = C1oeste         7 = L1oeste
*/

string getNomePista(int positPista) {
	string nomePista[14] = {"O1leste", "N1sul", "S1norte", "C1oeste", "C1leste", "N2sul", "S2norte", "L1oeste",
            "O1oeste", "N1norte", "S1sul", "N2norte", "S2sul", "L1leste"};
	return nomePista[positPista];
}
