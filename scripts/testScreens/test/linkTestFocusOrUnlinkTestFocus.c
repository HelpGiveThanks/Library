testScreens: test: linkTestFocusOrUnlinkTestFocus
#
#If tag has not yet been selected, then link it.
Set Variable [ $focus; Value:tagLocation::_Ltag ]
Go to Field [ ]
Select Window [ Name: "Setup"; Current file ]
If [ $focus & ¶ ≠ FilterValues ( test::kcfocusALL ; $focus & "¶" ) ]
#
Set Variable [ $currentfocuses; Value:test::kcfocusALL ]
Set Field [ test::kcfocusALL; $focus & "¶" & $currentfocuses ]
#
#Reset conditional formatting variable for focuses.
Set Variable [ $$focuses; Value:test::kcfocusALL ]
Go to Field [ ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Exit Script [ ]
End If
#
#If tag has been selected and is not in use,
#then unlink it.
If [ tagTestSubjectLocationNAME::inUse = "" ]
Set Variable [ $currentfocuses; Value:test::kcfocusALL ]
Set Field [ test::kcfocusALL; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $currentfocuses ) ≠ ValueCount ( Substitute ( $currentfocuses ; $focus & "¶" ; "" ) ) ;
Substitute ( $currentfocuses ; $focus & "¶" ; "" ) ;
Substitute ( $currentfocuses ; $focus ; "" )
) ]
Else
#
Show Custom Dialog [ Message: "This test section contains user test results.  Delete all of them, and then you can unlink this section from this general test inquiry."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Reset conditional formatting variable for focuses.
Set Variable [ $$focuses; Value:test::kcfocusALL ]
Go to Field [ ]
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
December 9, ଘ౮27 20:23:05 Library.fp7 - linkTestFocusOrUnlinkTestFocus -1-
