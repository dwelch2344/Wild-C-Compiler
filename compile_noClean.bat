wildc_comp.exe < wildc_program.wc > wildc_program.il
pause
cls
ilasm wildc_program.il
del wildc_program.il
pause
cls
wildc_program.exe
pause