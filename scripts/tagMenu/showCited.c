tagMenu: showCited
#
#If user is not in add mode then inform user they
#must be before the database will show them reference
#data. The reason for this is because the layout
#in the reference or learn window changes to the
#add tag from these windows to the Tag Menu
#item selected. So instead of having the system
#automatically go into add mode, the user must
#decide they want to do this and thus be expecting
#a change in the layouts. Otherwise this change
#could confuse a user. So at the cost of minor
#inconvience I have chosen not to have the system
#guess the user wants to go into add mode and is
#expecting the system to do that when they click
#one of these numbered buttons on the showEvenMore
#layouts.
#
#
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
End If
Set Window Title [ Current Window; New Title: "References" ]
Go to Layout [ $$citeLayout ]
#
#Prevent record loading script during loops to
#ﬁnd wanted record, which would slow down system.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Now loop thru all the records until the record
#that ﬁts the key is found.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ reference::_Lreference = $$cited ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Allow the record load script to run and run it.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
#
#Put focus back on Tag Menus window and conditionally
#format any items that may be linked to record
#in the other window.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
January 7, 平成26 16:37:58 Imagination Quality Management.fp7 - showCited -1-
