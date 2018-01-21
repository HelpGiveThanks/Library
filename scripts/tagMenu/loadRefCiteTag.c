January 19, 2018 14:10:30 Library.fmp12 - loadRefCiteTag -1-
tagMenu: loadRefCiteTag
#
#
#If in the Test or Report section, stop this
#script when first loading up an info record's
#references.
If [ $$stopWhenLoadingInfoRecordReferences ≠ ""
 or
$$stopLoadTagRecord ≠ "" ]
Exit Script [ ]
End If
#
#
#This script insures the user is exited from
#text fields when first navigated to a record.
Set Variable [ $$stopGoToKeyTag; Value:1 ]
#
Perform Script [ “enterShortOrLongTagField” ]
// Show Custom Dialog [ Title: "halt"; Message: "halt"; Default Button: “OK”, Commit: “No” ]
Halt Script
#
#
