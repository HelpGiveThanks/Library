tagMenu: CHUNKHealthLockedFields
#
#Users cannot delete locked copyright records, but
#they might edit them. This script insures any edits
#made are replaced with the content from the
#Creative Commons website.
#
If [ $$citationMatch = "health" ]
Go to Record/Request/Page
[ First ]
#
Loop
If [ 9072011223903376 = tagMenus::_Ltag or 9072011223903376 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "This media file is in the public domain in the United States." ]
Set Field [ tagMenus::tagSpelling; "This media file is in the public domain in the United States." ]
Set Field [ tagMenus::notesOrHealth; "This applies to U.S. works where the copyright has expired, often because its first publication occurred prior to January 1, 1923. " & ¶ & "
This image might not be in the public domain outside of the United States; this especially applies in the countries and areas that do not apply the rule of the shorter term for US works, such as Canada, Mainland China (not Hong Kong or Macao), Germany, Mexico, and
Switzerland. The creator and year of publication are essential information and must be provided. See Wikipedia:Public domain and Wikipedia:Copyrights for more details." ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 9072011221202374 = tagTable::_Ltag or 9072011221202374 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "This work is in the public domain in the United States, and those countries with a copyright term of life of the author plus 100 years or fewer." ]
Set Field [ tagMenus::tagSpelling; "This work is in the public domain in the United States, and those countries with a copyright term of life of the author plus 100 years or fewer." ]
Set Field [ tagMenus::notesOrHealth; "" ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 8172011134941327 = tagTable::_Ltag or 8172011134941327 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "Public domain in USA. This image (or other media file) is in the public domain because its copyright has expired." ]
Set Field [ tagMenus::tagSpelling; "Public domain in USA. This image (or other media file) is in the public domain because its copyright has expired." ]
Set Field [ tagMenus::notesOrHealth; "This applies to Australia, the European Union and those countries with a copyright term of life of the author plus 70 years." & ¶ & "
You must also include a United States public domain tag to indicate why this work is in the public domain in the United States. Note that a few countries have copyright terms longer than 70 years: Mexico has 100 years, Colombia has 80 years, and Guatemala and Samoa have
75 years. This image may not be in the public domain in these countries, which moreover do not implement the rule of the shorter term. Côte d'Ivoire has a general copyright term of 99 years and Honduras has 75 years, but they do implement the rule of the shorter term." ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 8102011220941282 = tagTable::_Ltag or 8102011220941282 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "All rights reserved by copyright holder (Do Not Share)" ]
Set Field [ tagMenus::tagSpelling; "All rights reserved by copyright holder (Do Not Share)" ]
Set Field [ tagMenus::notesOrHealth; "" ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 31620121743201228 = tagTable::_Ltag or 31620121743201228 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "No Known Copyright. WARNING: There may be copyrights reserved in some countries, locations, etc." ]
Set Field [ tagMenus::tagSpelling; "No Known Copyright. WARNING: There may be copyrights reserved in some countries, locations, etc." ]
Set Field [ tagMenus::notesOrHealth; "" ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 31620121746441229 = tagTable::_Ltag or 31620121746441229 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY 3.0 (Attribution 3.0 Unported)" ]
Set Field [ tagMenus::tagSpelling; "CC BY 3.0 (Attribution 3.0 Unported)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of the Legal Code " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 to Share — to copy, distribute and transmit the work" & ¶ & "
 to Remix — to adapt the work" & ¶ & "
 to make commercial use of the work" & ¶ & "
Under the following conditions:" & ¶ & "
 Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)." & ¶ & "
With the understanding that:" & ¶ & "
 Waiver — Any of the above conditions can be waived if you get permission from the copyright holder." & ¶ & "
 Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license." & ¶ & "
 Other Rights — In no way are any of the following rights affected by the license:" & ¶ & "
 Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;" & ¶ & "
 The author's moral rights;" & ¶ & "
 Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights." & ¶ & "
 Notice — For any reuse or distribution, you must make clear to others the license terms of this work. The best way to do this is with a link to this web page.
" ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 6282014220454904 = tagTable::_Ltag or 6282014220454904 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY 4.0 (Attribution 4.0 International)" ]
Set Field [ tagMenus::tagSpelling; "CC BY 4.0 (Attribution 4.0 International)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of (and not a substitute for) the license. " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 Share — copy and redistribute the material in any medium or format" & ¶ & "
 Adapt — remix, transform, and build upon the material" & ¶ & "
 for any purpose, even commercially." & ¶ & "
The licensor cannot revoke these freedoms as long as you follow the license terms." & ¶ & "
Under the following terms:" & ¶ & "
 Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use." & ¶ & "
No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits." & ¶ & "
Notices:" & ¶ & "
 You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation. " & ¶ & "
 No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. " ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 31620121837161231 = tagTable::_Ltag or 31620121837161231 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-NC 3.0 (Attribution-NonCommercial 3.0 Unported)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-NC 3.0 (Attribution-NonCommercial 3.0 Unported)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of the Legal Code " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 to Share — to copy, distribute and transmit the work" & ¶ & "
 to Remix — to adapt the work" & ¶ & "
Under the following conditions:" & ¶ & "
 Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)." & ¶ & "
 Noncommercial — You may not use this work for commercial purposes." & ¶ & "
With the understanding that:" & ¶ & "
 Waiver — Any of the above conditions can be waived if you get permission from the copyright holder." & ¶ & "
 Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license." & ¶ & "
 Other Rights — In no way are any of the following rights affected by the license:" & ¶ & "
 Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;" & ¶ & "
 The author's moral rights;" & ¶ & "
 Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights." & ¶ & "
 Notice — For any reuse or distribution, you must make clear to others the license terms of this work. The best way to do this is with a link to this web page.
" ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 6272014222057903 = tagTable::_Ltag or 6272014222057903 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-NC 4.0 (Attribution-NonCommercial 4.0 International)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-NC 4.0 (Attribution-NonCommercial 4.0 International)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of (and not a substitute for) the license. " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 Share — copy and redistribute the material in any medium or format" & ¶ & "
 Adapt — remix, transform, and build upon the material" & ¶ & "
The licensor cannot revoke these freedoms as long as you follow the license terms." & ¶ & "
Under the following terms:" & ¶ & "
 Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use." & ¶ & "
 NonCommercial — You may not use the material for commercial purposes." & ¶ & "
No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits." & ¶ & "
Notices:" & ¶ & "
 You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation. " & ¶ & "
 No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. " ]
May 10, 平成27 12:56:51 Library.fp7 - CHUNKHealthLockedFields -1-
tagMenu: CHUNKHealthLockedFields
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of (and not a substitute for) the license. " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 Share — copy and redistribute the material in any medium or format" & ¶ & "
 Adapt — remix, transform, and build upon the material" & ¶ & "
The licensor cannot revoke these freedoms as long as you follow the license terms." & ¶ & "
Under the following terms:" & ¶ & "
 Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use." & ¶ & "
 NonCommercial — You may not use the material for commercial purposes." & ¶ & "
No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits." & ¶ & "
Notices:" & ¶ & "
 You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation. " & ¶ & "
 No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. " ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 31620121841541232 = tagTable::_Ltag or 31620121841541232 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-SA 3.0 (Attribution-ShareAlike 3.0 Unported)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-SA 3.0 (Attribution-ShareAlike 3.0 Unported)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of the Legal Code " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
to Share — to copy, distribute and transmit the work" & ¶ & "
to Remix — to adapt the work" & ¶ & "
to make commercial use of the work" & ¶ & "
Under the following conditions:" & ¶ & "
Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)." & ¶ & "
Share Alike — If you alter, transform, or build upon this work, you may distribute the resulting work only under the same or similar license to this one.
With the understanding that:" & ¶ & "
Waiver — Any of the above conditions can be waived if you get permission from the copyright holder." & ¶ & "
Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license." & ¶ & "
Other Rights — In no way are any of the following rights affected by the license:" & ¶ & "
Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;" & ¶ & "
The author's moral rights;" & ¶ & "
Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights." & ¶ & "
Notice — For any reuse or distribution, you must make clear to others the license terms of this work. " ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 6282014225223905 = tagTable::_Ltag or 6282014225223905 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-SA 4.0 (Attribution-ShareAlike 4.0 International)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-SA 4.0 (Attribution-ShareAlike 4.0 International)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of (and not a substitute for) the license. " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 Share — copy and redistribute the material in any medium or format" & ¶ & "
 Adapt — remix, transform, and build upon the material" & ¶ & "
 for any purpose, even commercially." & ¶ & "
The licensor cannot revoke these freedoms as long as you follow the license terms." & ¶ & "
Under the following terms:" & ¶ & "
 Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use." & ¶ & "
ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original." & ¶ & "
No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits." & ¶ & "
Notices:" & ¶ & "
 You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation. " & ¶ & "
 No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. " ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 31620121902441234 = tagTable::_Ltag or 31620121902441234 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-ND 3.0 (Attribution-NoDerivs 3.0 Unported)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-ND 3.0 (Attribution-NoDerivs 3.0 Unported)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of the Legal Code" & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 to Share — to copy, distribute and transmit the work" & ¶ & "
 to make commercial use of the work" & ¶ & "
Under the following conditions:" & ¶ & "
 Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)." & ¶ & "
 No Derivative Works — You may not alter, transform, or build upon this work." & ¶ & "
With the understanding that:" & ¶ & "
 Waiver — Any of the above conditions can be waived if you get permission from the copyright holder." & ¶ & "
 Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license." & ¶ & "
 Other Rights — In no way are any of the following rights affected by the license:" & ¶ & "
 Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;" & ¶ & "
 The author's moral rights;" & ¶ & "
 Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights." & ¶ & "
 Notice — For any reuse or distribution, you must make clear to others the license terms of this work. The best way to do this is with a link to this web page." ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 6282014232807908 = tagTable::_Ltag or 6282014232807908 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-ND 4.0 (Attribution-NoDerivs 4.0 International)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-ND 4.0 (Attribution-NoDerivs 4.0 International)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of (and not a substitute for) the license. " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 Share — copy and redistribute the material in any medium or format" & ¶ & "
 for any purpose, even commercially." & ¶ & "
The licensor cannot revoke these freedoms as long as you follow the license terms." & ¶ & "
Under the following terms:" & ¶ & "
 Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use." & ¶ & "
 NoDerivatives — If you remix, transform, or build upon the material, you may not distribute the modified material." & ¶ & "
No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits." & ¶ & "
Notices:" & ¶ & "
 You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation. " & ¶ & "
 No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. " ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 8162011231825326 = tagTable::_Ltag or 8162011231825326 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-NC-SA 3.0 (Attribution-NonCommercial-ShareAlike 3.0 Unported)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-NC-SA 3.0 (Attribution-NonCommercial-ShareAlike 3.0 Unported)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of the Legal Code" & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing this link" & ¶ & "
You are free:" & ¶ & "
to Share — to copy, distribute and transmit the work" & ¶ & "
to Remix — to adapt the work" & ¶ & "
Under the following conditions:
" & ¶ & "
Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)." & ¶ & "
Noncommercial — You may not use this work for commercial purposes." & ¶ & "
Share Alike — If you alter, transform, or build upon this work, you may distribute the resulting work only under the same or similar license to this one." & ¶ & "
With the understanding that:" & ¶ & "
Waiver — Any of the above conditions can be waived if you get permission from the copyright holder." & ¶ & "
Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license." & ¶ & "
Other Rights — In no way are any of the following rights affected by the license:" & ¶ & "
Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;" & ¶ & "
The author's moral rights;" & ¶ & "
Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights." & ¶ & "
Notice — For any reuse or distribution, you must make clear to others the license terms of this work.
" ]
May 10, 平成27 12:56:51 Library.fp7 - CHUNKHealthLockedFields -2-
tagMenu: CHUNKHealthLockedFields
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of the Legal Code" & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing this link" & ¶ & "
You are free:" & ¶ & "
to Share — to copy, distribute and transmit the work" & ¶ & "
to Remix — to adapt the work" & ¶ & "
Under the following conditions:
" & ¶ & "
Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)." & ¶ & "
Noncommercial — You may not use this work for commercial purposes." & ¶ & "
Share Alike — If you alter, transform, or build upon this work, you may distribute the resulting work only under the same or similar license to this one." & ¶ & "
With the understanding that:" & ¶ & "
Waiver — Any of the above conditions can be waived if you get permission from the copyright holder." & ¶ & "
Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license." & ¶ & "
Other Rights — In no way are any of the following rights affected by the license:" & ¶ & "
Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;" & ¶ & "
The author's moral rights;" & ¶ & "
Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights." & ¶ & "
Notice — For any reuse or distribution, you must make clear to others the license terms of this work.
" ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 6282014225704906 = tagTable::_Ltag or 6282014225704906 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-NC-SA 4.0 (Attribution-NonCommercial-ShareAlike 4.0 International)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-NC-SA 4.0 (Attribution-NonCommercial-ShareAlike 3.0 International)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of (and not a substitute for) the license. " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 Share — copy and redistribute the material in any medium or format" & ¶ & "
Adapt — remix, transform, and build upon the material" & ¶ & "
The licensor cannot revoke these freedoms as long as you follow the license terms." & ¶ & "
Under the following terms:" & ¶ & "
 Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use." & ¶ & "
 NonCommercial — You may not use the material for commercial purposes." & ¶ & "
ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original." & ¶ & "
No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits." & ¶ & "
Notices:" & ¶ & "
 You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation. " & ¶ & "
 No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. " ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 121620112002051049 = tagTable::_Ltag or 121620112002051049 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-NC-ND 3.0 (Attribution-NonCommercial-NoDerivs 3.0 Unported)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-NC-ND 3.0 (Attribution-NonCommercial-NoDerivs 3.0 Unported)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of the Legal Code " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
to Share — to copy, distribute and transmit the work" & ¶ & "
Under the following conditions:" & ¶ & "
Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work)." & ¶ & "
Noncommercial — You may not use this work for commercial purposes." & ¶ & "
No Derivative Works — You may not alter, transform, or build upon this work." & ¶ & "
With the understanding that:" & ¶ & "
Waiver — Any of the above conditions can be waived if you get permission from the copyright holder." & ¶ & "
Public Domain — Where the work or any of its elements is in the public domain under applicable law, that status is in no way affected by the license." & ¶ & "
Other Rights — In no way are any of the following rights affected by the license:" & ¶ & "
Your fair dealing or fair use rights, or other applicable copyright exceptions and limitations;" & ¶ & "
The author's moral rights;" & ¶ & "
Rights other persons may have either in the work itself or in how the work is used, such as publicity or privacy rights." & ¶ & "
Notice — For any reuse or distribution, you must make clear to others the license terms of this work.
" ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 6282014230310907 = tagTable::_Ltag or 6282014230310907 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "CC BY-NC-ND 4.0 (Attribution-NonCommercial-NoDerivs 4.0 International)" ]
Set Field [ tagMenus::tagSpelling; "CC BY-NC-ND 4.0 (Attribution-NonCommercial-NoDerivs 4.0 International)" ]
Set Field [ tagMenus::notesOrHealth; "This is a human-readable summary of (and not a substitute for) the license. " & ¶ & "
Click the health tag-menu view button to reveal link to full code and translations of license if you are not currently seeing the link" & ¶ & "
You are free:" & ¶ & "
 Share — copy and redistribute the material in any medium or format." & ¶ & "
The licensor cannot revoke these freedoms as long as you follow the license terms." & ¶ & "
Under the following terms:" & ¶ & "
 Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use." & ¶ & "
 NonCommercial — You may not use the material for commercial purposes." & ¶ & "
NoDerivatives — If you remix, transform, or build upon the material, you may not distribute the modified material." & ¶ & "
No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits." & ¶ & "
Notices:" & ¶ & "
 You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation. " & ¶ & "
 No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material. " ]
Set Field [ citationPicture1::kcsection; "" ]
#
Else If [ 31620121911511235 = tagTable::_Ltag or 31620121911511235 = tagMenus::_Ltag ]
Set Field [ tagMenus::tag; "No rights reserved by the creator of the work." ]
Set Field [ tagMenus::tagSpelling; "No rights reserved by the creator of the work." ]
Set Field [ tagMenus::notesOrHealth; "I give up all rights to and ask for no credit for my work." ]
Set Field [ citationPicture1::kcsection; "" ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
Go to Record/Request/Page
[ First ]
#
May 10, 平成27 12:56:51 Library.fp7 - CHUNKHealthLockedFields -3-
