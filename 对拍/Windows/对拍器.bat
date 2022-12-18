:again
scq.exe > 1.in
bl.exe < 1.in > bl.out
sf.exe < 1.in > sf.out
fc bl.out sf.out
if not errorlevel 1 goto again
pause