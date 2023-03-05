*Baliza - Bitdefender Challenge @ UPB 2022 <br>*

Spam Detector used to identify spam emails from an archive.

**input:** <br>
:open_file_folder: *data/* directory <br>
&emsp; |--- :open_file_folder: *emails/* &rarr; archive of emails (some are spam, some are not) <br>
&emsp; |--- :page_facing_up: *keywords* &rarr; list of keywords commonly found in spam emails <br>
&emsp; |--- :page_facing_up: *spammers* &rarr; list of email addresses known to be spam <br>

**output:** <br>
:page_facing_up: *statistics.out* &rarr; information about the number of apparitions of keywords in all emails, as well as the
                          standard deviation: *\<word> \<count> \<stdev>* <br>
:page_facing_up: *prediction.out* &rarr; each line i contains a binary value representing whether the $i^{th}$ email is considered
                          to be spam (1) or not (0) <br>

Email structure: <br>
>*Date: \<date\>*<br>
>*Subject: \<email subject\>*<br>
>*From: \<email address of sender\>*<br>
>
>*Body: \<email text\>*

:page_facing_up: ****keywords additional_keywords**** <br>
Contain lists of keywords commonly found in spam emails. The words are considered to be case insensitive.
For each keyword we calculate the standard deviation:
$$stdev=\sqrt{\frac{1}{n}\sum_{i=1}^{n}(v_i-mean)^2}$$

The standard deviation is used to measure how dispersed a dataset is in relation to the mean (expected value). <br>
A low value of the standard deviation indicates that the values tend to be close to the mean. A high standard
deviation suggests that data is more dispersed, therefore certain keywords may appear more times in spam emails. <br>

Other criteria for identifying spam emails: <br>
- uppercase characters frequency
- email body length
- sender email address found in collection of known spammes (spammers input file)
