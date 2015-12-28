pictures: pictureReplaceButton
#
#
#If the primary node for this record locked
#then prevent it from being changed.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Exit Script [ ]
End If
#
#Enable media to be replaced.
Set Variable [ $$replaceButton; Value:1 ]
Perform Script [ “pictureInsert” ]
Set Variable [ $$replaceButton ]
December 27, ଘ౮27 19:53:29 Library.fp7 - pictureReplaceButton -1-
