July 21, 2018 14:14:05 Library.fmp12 - loadReferenceForInsertIntoText -1-
tagMenu: loadReferenceForInsertIntoText
#
#
#Stop the script if the user is just loading up
#the references.
If [ $$STOPloadReferenceForInsertIntoText = 1 ]
Exit Script [ ]
End If
#
#Set the reference template selections shown
#in the top menu section.
Set Field [ TEMP::referenceInsertText; reference::referenceUsedInTextToRefReference ]
#
#Exit the field the user just clicked into.
Go to Field [ ]
#
#
