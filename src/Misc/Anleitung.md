# Anleitung
In dieser Anleitung wird kurz der Umgang mit der App erklärt.

# Menüführung
Die Menüführung geschieht über die Pfeiltasten. Eine Auswahl wird über die Enter Taste getroffen.

## Neues Spiel
Nachdem eine Schwierigkeit ausgewählt wird, wird ein neues Spiel generiert.

- Leicht: 20 Zellen sind leer.
- Mittel: 35 Zellen sind leer.
- Schwierig: 50 Zellen sind leer.

Das Spiel wird, beim beenden, in die last_save Datei geschrieben, das letzte gespeicherte wird somit überschrieben.

## Spiel Fortsetzen
Das letzte gespeicherte Spiel wird fortgesetzt. Wenn aktuell kein unbeendetes Spiel existiert, wird dies angezeigt.

## Datei laden
Es werden, dynamisch, die ersten 50 Einträge im Ordner *./sudokus*, auf 10 Seiten (5 Einträge pro Seite) angezeigt. Ein Spiel kann ausgewählt über die normale Menüführung ausgewählt werden. Wenn das gewählte Sudoku nicht lösbar ist, wird es nicht geladen.

Wenn keine Sudokus in dem Ordner existieren, wird dies angezeigt.

## Editor
Man kann sich entscheiden, ob man ein bereits existierendes Sudoku bearbeiten oder ein neues erstellen möchte. Wenn eines bearbeitet wird, wird das "Datei laden" Menü angezeigt. Ansonsten wird ein leeres Sudoku geladen.

Im Editor kann nach Belieben ein Sudoku erstellt werden.

Bei Druck auf Escape wird überprüft, ob das erstellte Sudoku lösbar ist. Fall es das ist, wird ein Name abgefragt, wenn es neu erstellt wurde oder es wird in die bereits existierende Datei geschrieben, falls es bearbeitet wurde.

Ist das Sudoku nicht lösbar, bekommt man hier einen Prompt.


# Spiel spielen
- Im Sudoku wird über die **Pfeiltasten** navigiert. 
- Zellen, die nicht bereits gefüllt sind (*weiß*), können mit den Zahlen von 1-9 gefüllt werden, in dem diese Zahl eingegeben wird. 
- User-Eingaben werden in *blau* angezeigt.
- Hinweise können durch Drücken der Taste **H** generiert werden. Diese Hinweise sind zufällig generiert und werden in *rot* angezeigt.
- Bearbeitbare Felder (nicht vom System gefüllt und kein Hinweis), können auch wieder, durch drücken von **Backspace** wieder gelöscht werden.
- Durch Druck auf **Escape** wird das Spiel beendet. Der Aktuelle Spielstand wird unter *./saves/last_save.txt* gespeichert.
- Wenn das Sudoku korrekt gelöst ist, wird ein Prompt angezeigt, dass es gelöst ist.
- Nachdem das Sudoku gelöst ist, wird überprüft, ob die gespielte Zeit besser als die beste gespeicherte Zeit ist. Falls ja, wird diese in einer Textdatei gespeichert und beim nächsten Spiel auf der gleichen Schwierigkeitsstufe geladen. Hier wird zwischen zufällig generierten und selbst erstellten Sudokus, sowie Schwierigkeitsstufen unterscheiden.



# Sudoku Regeln
Das Sudoku Feld wird mit Zahlen von 1-9 nach folgenden Regeln gefüllt:

- Jede Zahl von 1-9 kann in jeder **Spalte** nur einmal vorkommen.
- Jede Zahl von 1-9 kann in jeder **Zeile** nur einmal vorkommen.
- Jede Zahl von 1-9 kann in jedem **3x3 Kasten** nur einmal vorkommen.