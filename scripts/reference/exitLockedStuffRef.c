January 17, 2018 23:22:01 Library.fmp12 - exitLockedStuffRef -1-
reference: exitLockedStuffRef
#
#Stop script if user has just clicked on this
#record and it is still loading.  
If [ $$turnOffRefStuffExitScript = 1 ]
Exit Script [ ]
End If
#
#Exit field user is in.
Go to Field [ ]
#
#In stuff mode when changes are made to a
#reference record, if it is unlocked then backup
#those changes, so if it is locked in the future
#and changes are made, they can be overwritten
#with the saved backup data.
If [ TEMP::InventoryLibraryYN ≠ "" ]
#
#
#If the record is unlocked, then save any
#changes in the backup data fields.
If [ refCreatorNode::orderOrLock = "" ]
#
#
#Only change records that have been changed.
#Changes result in the record modify date being
#reset, and this should only be done when the
#user modifies the record.
If [ reference::Title[1] ≠ reference::Title[2] ]
Set Field [ reference::Title[2]; reference::Title[1] ]
End If
If [ reference::thoughtsNotesEtc[1] ≠ reference::thoughtsNotesEtc[2] ]
Set Field [ reference::thoughtsNotesEtc[2]; reference::thoughtsNotesEtc[1] ]
End If
If [ reference::publicationYearOrStuffOrderNumber[1] ≠ reference::publicationYearOrStuffOrderNumber[2] ]
#
#Insure that only 3 digit numbers are
#saved in this field.
Set Variable [ $threeDigitNumber; Value:Right ( GetAsNumber (reference::publicationYearOrStuffOrderNumber[1]) ;
3 ) ]
Set Field [ reference::publicationYearOrStuffOrderNumber[2]; $threeDigitNumber ]
Set Field [ reference::publicationYearOrStuffOrderNumber; $threeDigitNumber ]
End If
#
#
#If the record is locked, then replace any
#changes with the saved back up data.
Else If [ refCreatorNode::orderOrLock ≠ "" ]
#
#
#Only change records that have been changed.
#Changes result in the record modify date being
#reset, and this should only be done when the
#user modifies the record.
If [ reference::Title[1] ≠ reference::Title[2] ]
Set Field [ reference::Title; reference::Title[2] ]
End If
If [ reference::thoughtsNotesEtc[1] ≠ reference::thoughtsNotesEtc[2] ]
Set Field [ reference::thoughtsNotesEtc; reference::thoughtsNotesEtc[2] ]
End If
If [ reference::publicationYearOrStuffOrderNumber[1] ≠ reference::publicationYearOrStuffOrderNumber[2] ]
Set Field [ reference::publicationYearOrStuffOrderNumber; reference::publicationYearOrStuffOrderNumber[2] ]
End If
#
#Inform the user why the cannot change the
#locked record's data.
Show Custom Dialog [ Message: "The node that created this record — " & refCreatorNode::tag & " — is locked. Select this
node in the setup window and enter the password to unlock it, then you will able to edit records assigned to it."; Default
Button: “OK”, Commit: “Yes” ]
End If
#
#
End If
#
#
