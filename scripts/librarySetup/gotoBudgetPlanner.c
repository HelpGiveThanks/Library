September 10, 2018 16:33:57 Library.fmp12 - gotoBudgetPlanner -1-
librarySetup: gotoBudgetPlanner
#
#Open using this url on iPad/iPhone.
If [ Get ( SystemPlatform ) = 3 ]
Open URL [ "fmp://%7e/BudgetPlanner" ]
[ No dialog ]
Close Window [ Name: "All Apps"; Current file ]
Halt Script
End If
#
Select Window [ Name: "Budget Planner" ]
If [ Get (LastError) = 112 ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "budgetplanner" ) ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "budgetplanner" ) ]
[ No dialog ]
End If
#
#This logic is the same for going to all apps in
#each HGT application. So if you change it,
#change it everywhere.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The BudgentPlanner's name has been changed or it is not in its required folder:
0penME_YourFilesAreHere."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "If the name is correct (BudgentPlanner) and it is in the correct folder
(0penME_YourFilesAreHere), then check if the file types are either all .fmp12 or . HFG2 files."; Default Button: “OK”, Commit:
“Yes” ]
Show Custom Dialog [ Message: "Click the HelpGiveThanks Website button to find out how to get a new copy of the
BudgentPlanner if needed."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Open the folder — 0penME_YourFilesAreHere — so you can check on this app, or put it in this
folder?"; Default Button: “yes”, Commit: “Yes”; Button 2: “no”, Commit: “No” ]
If [ Get (LastMessageChoice) = 1 ]
Open URL [ Substitute (
Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) )
 ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) ) ]
[ No dialog ]
End If
#
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The folder name — 0penME_YourFilesAreHere — has been changed, or this folder
has been moved."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
End If
#
#Close all solutions window.
If [ $$otherApps = 1 ]
Set Variable [ $$otherApps ]
Close Window [ Name: "All Apps"; Current file ]
Halt Script
End If
#
