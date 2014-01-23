tagMenu: addTagToTestSubject
#
#Get key for tag that is to be added to record.
If [ Get (LayoutName) ≠ "defaultLocation" ]
Set Variable [ $tag; Value:tagMenus::_Ltag ]
Else If [ Get (LayoutName) = "defaultLocation" ]
Set Variable [ $tag; Value:tagTestSubjectLocation::knode ]
End If
#
#Remove focus from ﬁeld so can see
#conditional formatting.
Go to Field [ ]
#
#Conditionally format selected tag.
If [ Get (LayoutName) ≠ "defaultLocation" ]
Set Variable [ $$testSubject; Value:tagMenus::_Ltag ]
Else If [ Get (LayoutName) = "defaultLocation" ]
Set Variable [ $$testSubject; Value:tagTestSubjectLocation::knode ]
End If
#
#Select reference, learn, or setup window.
Select Window [ Name: "Setup"; Current ﬁle ]
#
#If test subject node is in use, then remove it.
If [ tempSetup::kdefaultNodeTestSubject = $tag ]
Set Field [ tempSetup::kdefaultNodeTestSubject; "" ]
#
#Finish removing the key.
Set Variable [ $$testSubject ]
#
#If primary node is not in use add it.
Else If [ tempSetup::kdefaultNodeTestSubject ≠ $tag ]
Set Field [ tempSetup::kdefaultNodeTestSubject; $tag ]
Set Variable [ $$testSubject; Value:tempSetup::kdefaultNodeTestSubject ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a ﬁnd requiring the newly added key.
Commit Records/Requests
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
Exit Script [ ]
End If
#
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
January 7, 平成26 16:06:49 Imagination Quality Management.fp7 - addTagToTestSubject -1-
