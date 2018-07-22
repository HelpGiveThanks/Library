July 20, 2018 17:25:57 Library.fmp12 - gotoBudgetPlanner -1-
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
#Close all solutions window.
If [ $$otherApps = 1 ]
Set Variable [ $$otherApps ]
Close Window [ Name: "All Apps"; Current file ]
Halt Script
End If
