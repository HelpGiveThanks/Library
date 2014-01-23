reference(citation): HelpReferenceFields
Set Variable [ $objectName; Value:Middle ( Get ( ActiveLayoutObjectName ) ; 2 ; 2 ) ]
Set Field [ TEMP::Help; TEMP::Help [$objectName] ]
Go to Field [ ]
Select Window [ Name: "Reference Field Help"; Current ﬁle ]
If [ Get ( LastError ) ≠ 0 ]
New Window [ Name: "Reference Field Help"; Left: Get ( WindowWidth ) ]
End If
Go to Layout [ “ReferenceHelp” (reference) ]
Select Window [ Name: "Reference Field Help"; Current ﬁle ]
January 7, 平成26 18:01:32 Imagination Quality Management.fp7 - HelpReferenceFields -1-
