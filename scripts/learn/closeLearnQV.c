July 20, 2018 17:18:32 Library.fmp12 - closeLearnQV -1-
learn: closeLearnQV
#
#Go to reference record layout.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ $$testLearnLayoutName ]
Set Variable [ $$testLearnLayoutName ]
Set Variable [ $$stoploadCitation ]
#
#Allow add mode.
Set Variable [ $$stopAdd ]
#
#Capture note and timestamp. If these are
#changed while on the Qv layout it will effect
#the record's sort location and require a resort
#for the user to see the record they went to the
#QV window to look at.
If [ $$QvNote ≠ testlearn::note
 or
$$QvLocation ≠ testlearn::orderInventoryGroupNumber
 or
$$QvTimestamp ≠ testlearn::timestamp ]
Set Variable [ $$QvNote ]
Set Variable [ $$QvLocation ]
Set Variable [ $$QvTimestamp ]
Sort Records [ ]
[ No dialog ]
End If
