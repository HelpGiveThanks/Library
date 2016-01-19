learn: storageAreaLayoutCheckBox
#
#Prevent user from tagging storage records
#with other storage tags. I.E., No storage
#inside of storage relationships allowed.
If [ TEMP::InventoryLibaryYN = "" ]
Exit Script [ ]
End If
#
If [ Filter (testlearn::kcreference ; "L") ≠ "" ]
Set Field [ testlearn::sampleCasePoint; "" ]
Show Custom Dialog [ Message: "This item is in storage. To make it a storage location first remove it from storage. On the Tag
Menu's window 1) click 'it's here', 2) click 'containers', and 3) click the button next to storage area where it is located.";
Buttons: “OK” ]
Exit Script [ ]
End If
#
January 18, ଘ౮28 16:18:06 Library.fp7 - storageAreaLayoutCheckBox -1-
