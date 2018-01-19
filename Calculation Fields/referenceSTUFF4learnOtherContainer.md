//Keyword
If ( Title ≠ "" ; Title & " " ; "" )  &

//Keyword Group Label
TextColor (  

If ( kkeywordPrimary = "" ; "" ;  tagKeywordPrimary::tag ) &

If ( kkeywordOther = "" ; "" ; ", " & OtherKeyWords )

; RGB ( 130 ; 130 ; 130 ) )
