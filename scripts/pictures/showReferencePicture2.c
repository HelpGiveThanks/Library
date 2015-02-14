pictures: showReferencePicture2
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
#inconvience I have choose not to have the system
#guess the user wants to go into add mode and is
#expecting the system to do that when they click
#one of these numbered buttons on the showEvenMore
#layouts.
If [ $$add = "" ]
Show Custom Dialog [ Message: "Click the 'add' button above and then click this button to see citation for this item. "; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If the field is blank then stop the script.
#No poin in looking for a record where there isn't one.
If [ tagMenus::Kpicture2 = "" ]
Exit Script [ ]
End If
#
#Capture the key to unlock the record it belongs to.
Set Variable [ $key; Value:tagMenus::Kpicture2 ]
#
#Determine if the key comes from the testlearn
#table, and if so perform these script steps.
If [ TLPicture2::_Ltestlearn ≠ "" ]
#
#Select the correct window and then change its
#name if neccessary to match the table the
#records are coming from.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
End If
Set Window Title [ Current Window; New Title: "Learn" ]
Go to Layout [ <unknown> ]
#
#Prevent record loading script during loops to
#find wanted record, which would slow down system.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Now loop thru all the records until the record
#that fits the key is found.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $key ]
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
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Determine if the key comes from the reference
#table, and if so perform these script steps.
Else If [ citationPicture2::_Lreference ≠ "" ]
#
#Select the correct window and then change its
#name if neccessary to match the table the
#records are coming from.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
End If
Set Window Title [ Current Window; New Title: "References" ]
Go to Layout [ “ReferenceAddToTag” (reference) ]
#
#Prevent record loading script during loops to
#find wanted record, which would slow down system.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Now loop thru all the records until the record
#that fits the key is found.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ reference::_Lreference = $key ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If key is not found in this section's set of records
#then look for it in the other sections.
If [ reference::_Lreference ≠ $key ]
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $key ]
Extend Found Set [ ]
End If
#
#Allow the record load script to run and run it.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
#
#Put focus back on Tag Menus window and conditionally
#format any items that may be linked to record
#in the other window.
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
End If
January 7, 平成26 17:19:17 Imagination Quality Management.fp7 - showReferencePicture2 -1-
