January 18, 2018 15:35:53 Library.fmp12 - showCitation -1-
reference: showCitation
#
#Capture the key to unlock the record it belongs to.
Set Variable [ $key; Value:reference::_Lreference ]
#
#Select the correct window and then change its
#name if neccessary to match the table the
#records are coming from.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
End If
Set Variable [ $$cited; Value:reference::_Lreference ]
Set Variable [ $$citeLayout; Value:Get (LayoutName) ]
Set Window Title [ Current Window; New Title: "References" ]
Go to Layout [ “Reference” (reference) ]
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
#Allow the record load script to run and run it.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord (update name change loadCitation)” ]
#
#Return to Tag Menus window and conditionally
#format any items that may be linked to record
#in the other window.
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
