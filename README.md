# WP-Project-Mortal-Combat-Game
Fakultet elektrotehnike Tuzla - Windows programiranje 

Radni naziv projekta (programa): Mortal Kombat (Lite Version)
Kratak opis projekta:
Ovaj projekat će biti baziran na popularnoj igri Mortal Kombat. 
Kako nije moguće vremenski stići odraditi svaki segment igre, ovo će biti Lite verzija (pojednostavljena). 

Plan:
Igra će biti realizovana kao lokalni multiplayer, odnosno dva igrača će moći igrati na jednom računaru. 
Svaki igrač kontroliše svog karaktera uz pomoć tipki sa tastature,
a cilj je da koristeći razne borilačke vještine dovede broj života protivnika na nulu.
Igrač čiji karakter dođe na ovu vrijednost smatra se gubitnikom.
Originalna igra sadrži veliki broj karaktera koji imaju različite vrste napada i mogućnosti,
dok će ovaj projekat imati najviše 2 različita borca (pri čemu je moguće da oba igrača izaberu istog borca i bore se jedan protiv drugog).
Takođe, igrači će imati mogućnost da odaberu različite vrste arena za borbu. 
Svaka arena će biti specifična i imat će specijalne animacijske efekte koji daju ljepši vizualni izgled ali ne utiču direktno na samu borbu igrača. 
Kako vodimo računa da igra ima lijepe i kvalitetne vizualne osobine, 
dodatno vrijeme ćemo uložiti na izradu samih sprite sheetova za karaktere i arene. 
Animacije za karaktere su većinom sa interneta, a mi onda te animacije pretvaramo u sprite sheet. 
Arene su slike arena iz originalne igre Mortal Kombat,
ali u posebnim programima ćemo dodati na njih određene vrste animacije (magla, vjetar, snijeg i slično),
te nakon toga slijedi pretvaranje u sheet.

Na početku igre igračima se nudi mogućnost odabira likova i arene nakon čega počinje borba. 
Tokom borbe cijelo vrijeme će biti odgovarajuća pozadinska muzika (atmosferna),
a dodatni zvučni efekti će biti i prilikom borbe samih boraca.
U toku borbe borac se može naći u više položaja (odbrambeni - pri čemu blokira određene udarce protivnika,
ošamućeni - kada primi više udaraca za redom od protivnika).  Postojat će timer, koji ukoliko istekne,
borac sa većim trenutnim brojem života pobjeđuje. 
