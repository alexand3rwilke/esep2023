Dieses Projekt demonstriert das Testen einer Unit (in diesem Fall einer Klasse) in C++ mittels des GoogleTest Framework. Es ist ein "mitmach Projekt"; ihr müsst also noch selber Hand anlegen, damit das ganze funktioniert!

## Projektstruktur

Die hier verwendete Projektstruktur ist lediglich Natur persönlicher Präferenz und kein Standard, auch wenn sie an ein klassisches Maven Repository erinnert.

Es muss unterschieden werden, ob die "Buissness Logik" ausgeführt werden soll oder die Tests. Dies lässt sich entweder mittels Programmparameter über die Kommandozeile machen, oder mittels Präprozessoranweisungen beim Kompilieren. Hier ist letzteres verwendet worden, um die jeweilige `main` Funktion zu kompilieren.

Beim Ausführen sucht sich das Google Test Framework dann mittels eines Aufrufes die jeweiligen definierten Test Makros selbst raus und führt die Tests durch.

## Requirements

Da wir eine externe library benutzen muss diese über das Makefile eingebunden werden.

Darüber hinaus ist es notwendig, dass die statischen kompilierten sourcen auf dem Zielsystem vorhanden sind. In den VM's ist die GoogleTest library nicht mit vorinstalliert. Sie wird aber mit dem QNX sdk mitgeliefert und kann somit manuell auf dem Zielsystem nachinstalliert werden. Finden tut ihr die library unter `<home directory>/qnx700/target/<cpu-architecture>/usr/lib/libgtest.so.<version>`. Diese Datei muss dann auf euerm Zielsystem unter `/usr/lib/` abgelegt werden. Dazu könnt ihr den `Target File System Navigator` benutzen. Diesen findet ihr in der Menüleiste von Momentics unter `Window > Show View > Target File System Navigator`. Tut ihr das nicht bekommt ihr den Fehler ```ldd:FATAL: Could not load library libgtest.so.<version>```

## Test Runner

Ähnlich wie bei Java und JUnit kann man sich die Tests schön anzeigen lassen. Dazu stellt man bei den Konfigurationseinstellungen (Zahnrad beim Projekt Dropdown-Menü) unter `Arguments` den Testrunner auf `Google Tests Runner`.