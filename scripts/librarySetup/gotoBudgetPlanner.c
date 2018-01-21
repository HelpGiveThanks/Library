January 11, 2018 18:48:18 Library.fmp12 - gotoBudgetPlanner -1-
librarySetup: gotoBudgetPlanner
#
#Open using this url on iPad/iPhone.
If [ Get ( SystemPlatform ) = 3 ]
Open URL [ "fmp://%7e/Budget%20Planner" ]
Exit Script [ ]
End If
#
Select Window [ Name: "Budget Planner" ]
If [ Get (LastError) = 112 ]
Open URL [ Case ( Get ( SystemPlatform ) = - 2 ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file:/" )
& "Budget Planner." & Right ( Get ( FilePath ) ; 3 )
 ; " " ; "%20" ) ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file://" )
& "Budget Planner." & Right ( Get ( FilePath ) ; 3 )
 ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Open URL [ Case ( Get ( SystemPlatform ) = - 2 ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file:/" )
& "Budget Research.HG2"
 ; " " ; "%20" ) ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file://" )
& "Budget Research.HG2"
 ; " " ; "%20" ) ) ]
[ No dialog ]
End If
End If
#
#Close all solutions window.
If [ $$otherApps = 1 ]
Set Variable [ $$otherApps ]
Close Window [ Name: "All Solutions"; Current file ]
End If
