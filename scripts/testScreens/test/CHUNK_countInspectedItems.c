testScreens: test: CHUNK_countInspectedItems
#record the number of recommendations already counted for this item add 1 to it
Set Variable [ $count; Value:testlearn::InspectionItemCount ]
Set Field [ testlearn::InspectionItemCount; $count + 1 ]
January 7, 平成26 12:44:12 Imagination Quality Management.fp7 - CHUNK_countInspectedItems -1-
