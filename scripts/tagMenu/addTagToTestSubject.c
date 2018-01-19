January 15, 2018 16:49:51 Library.fmp12 - selectTestSubject -1-
tagMenu: selectTestSubject
#
#Get selected node's key.
Set Variable [ $tag; Value:tagMenus::_Ltag ]
Set Variable [ $TSname; Value:tagMenus::tag ]
#
#Leave field so user can see
#conditional formatting.
Go to Field [ ]
#
#Conditionally format selected node.
Set Variable [ $$testSubject; Value:tagMenus::_Ltag ]
#
#If node is the selected test subject,
#then unselect it.
If [ tempSetup::kdefaultNodeTestSubject = $tag ]
Set Field [ tempSetup::kdefaultNodeTestSubject; "" ]
Set Field [ tempSetup::DEFAULTNodeTestSubjectName; "" ]
Set Field [ tempSetup::testSubjectNodeIsLocked; "" ]
#
#Finish removing the key.
Set Variable [ $$testSubject ]
#
#If the selected node is not the selected test
#subject, then select it.
Else If [ tempSetup::kdefaultNodeTestSubject ≠ $tag ]
Set Field [ tempSetup::kdefaultNodeTestSubject; $tag ]
Set Variable [ $$testSubject; Value:tempSetup::kdefaultNodeTestSubject ]
Set Field [ tempSetup::DEFAULTNodeTestSubjectName; $TSname ]
If [ tagMenus::orderOrLock ≠ "" ]
Set Field [ tempSetup::testSubjectNodeIsLocked; 1 ]
Else
Set Field [ tempSetup::testSubjectNodeIsLocked; "" ]
End If
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a find requiring the newly added key.
Commit Records/Requests
#
#Select the default copyright for this node if blank.
If [ tagMenus::notesOrCopyright = "" ]
Set Field [ tagMenus::notesOrCopyright; TEMP::kdefaultCopyright ]
Show Custom Dialog [ Message: "Because this node's copyright was blank it was given the library's default copyright.";
Default Button: “OK”, Commit: “Yes” ]
End If
#
Refresh Window
Exit Script [ ]
End If
#
#Apply conditional formatting.
Refresh Window
#
