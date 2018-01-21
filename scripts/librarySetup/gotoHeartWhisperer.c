January 11, 2018 18:57:41 Library.fmp12 - gotoHeartWhisperer -1-
librarySetup: gotoHeartWhisperer
#
#Open using this url on iPad/iPhone.
If [ Get ( SystemPlatform ) = 3 ]
Open URL [ "fmp://%7e/Heart%20Whisperer" ]
Exit Script [ ]
End If
#
Select Window [ Name: "Icons" ]
Select Window [ Name: "Workout Editor" ]
Select Window [ Name: "Plan Week" ]
Select Window [ Name: "My Workouts" ]
Select Window [ Name: "Planned Workouts" ]
If [ MemorySwitch::fatPath = "Workout Editor" ]
Select Window [ Name: "Icons" ]
Select Window [ Name: "Workout Editor" ]
Select Window [ Name: "Plan Week" ]
Else If [ MemorySwitch::fatPath = "Plan Week" ]
Select Window [ Name: "Icons" ]
Select Window [ Name: "Workout Editor" ]
Select Window [ Name: "Plan Week" ]
Else If [ MemorySwitch::fatPath = "Icons" ]
Select Window [ Name: "Icons" ]
Select Window [ Name: "Workout Editor" ]
Select Window [ Name: "Plan Week" ]
Else If [ MemorySwitch::fatPath = "My Workouts" ]
Select Window [ Name: "My Workouts" ]
Select Window [ Name: "Planned Workouts" ]
Else If [ MemorySwitch::fatPath = "Planned Workouts" ]
Select Window [ Name: "My Workouts" ]
Select Window [ Name: "Planned Workouts" ]
End If
Select Window [ Name: MemorySwitch::fatPath ]
If [ Get (LastError) = 112 ]
Open URL [ Case ( Get ( SystemPlatform ) = - 2 ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file:/" )
& "Heart Whisperer." & Right ( Get ( FilePath ) ; 3 )
 ; " " ; "%20" ) ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file://" )
& "Heart Whisperer." & Right ( Get ( FilePath ) ; 3 )
 ; " " ; "%20" ) ) ]
[ No dialog ]
If [ Get (LastError) = 5 ]
Open URL [ Case ( Get ( SystemPlatform ) = - 2 ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file:/" )
& "Heart Whisperer.HG2"
 ; " " ; "%20" ) ;
Substitute (
Substitute (Left (Get (FilePath) ; Length ( Get (FilePath) ) - ( Length ( Get (FileName) ) + 4 ) ) ; "file:/" ; "file://" )
& "Heart Whisperer.HG2"
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
