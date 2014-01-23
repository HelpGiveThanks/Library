testScreens: test: linkTestFocusOrUnlinkTestFocus
#
#If tag has not yet been selected, then link it.
Set Variable [ $focus; Value:tagLocation::_Ltag ]
Go to Field [ ]
Select Window [ Name: "Setup"; Current ﬁle ]
If [ $focus & ¶ ≠ FilterValues ( test::kcfocusALL ; $focus & "¶" ) ]
#
Set Variable [ $currentfocuses; Value:test::kcfocusALL ]
Set Field [ test::kcfocusALL; $focus & "¶" & $currentfocuses ]
#
#Reset conditional formatting variable for focuses.
Set Variable [ $$focuses; Value:test::kcfocusALL ]
Go to Field [ ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
Exit Script [ ]
End If
#
#If tag has been selected, then unlink it.
Set Variable [ $currentfocuses; Value:test::kcfocusALL ]
Set Field [ test::kcfocusALL; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( $currentfocuses ) ≠ ValueCount ( Substitute ( $currentfocuses ; $focus & "¶" ; "" ) ) ;
Substitute ( $currentfocuses ; $focus & "¶" ; "" ) ;
Substitute ( $currentfocuses ; $focus ; "" )
) ]
#
#Reset conditional formatting variable for focuses.
Set Variable [ $$focuses; Value:test::kcfocusALL ]
Go to Field [ ]
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
January 7, 平成26 12:26:07 Imagination Quality Management.fp7 - linkTestFocusOrUnlinkTestFocus -1-
