July 20, 2018 17:26:11 Library.fmp12 - gotoHeartWhisperer -1-
librarySetup: gotoHeartWhisperer
#
#Open using this url on iPad/iPhone.
If [ Get ( SystemPlatform ) = 3 ]
Open URL [ "fmp://%7e/HeartWhisperer" ]
[ No dialog ]
Close Window [ Name: "All Apps"; Current file ]
Halt Script
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
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "heartwhisperer" ) ]
[ No dialog ]
Open URL [ Substitute ( MemorySwitch::helpPath ; "help" ; "heartwhisperer" ) ]
[ No dialog ]
End If
#
#Close all apps window.
If [ $$otherApps = 1 ]
Set Variable [ $$otherApps ]
Close Window [ Name: "All Apps"; Current file ]
Halt Script
End If
