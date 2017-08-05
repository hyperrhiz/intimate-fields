---
layout: default
title: "Intimate Fields | Twitter Implementation"
author: Intimate Fields
subtitle: 
description: "Instructions for setting up a twitterbot to tweet posies"
---
### Twitter Implementation


<img src="img/twitter.jpg" class="img-responsive">


Make a Posie Bot that remixes historical posies into new ones. (Ours tweets [@intimatefields](https://twitter.com/intimatefields))

#### Before You Start

1. Set up a twitter account. You’ll need a phone number to do this, so if you have an existing Twitter account attached to your phone number, make sure you go into your existing account, delete the mobile number, and log out again. You can add it back again later once your new bot is working.

2. Set up a Twitter app. Go to apps.twitter.com, sign in as your new bot account, and set up a new app. You’ll need to take note of four numbers: the **Consumer Key**, **Consumer Secret**, **Access Token** and **Access Secret** (to get these last two, clink on "create my access token" at the bottom of the page).

From here, you have two choices, depending on your resources. If you have access to Google Docs, you can run a bot easily using method #1. If you prefer to run the bot from your own server, choose method 2.

***
#### Method 1 (easiest option)

If you have a Google Docs account, head on over to Zach Whalen’s site [here](http://www.zachwhalen.net/posts/how-to-make-a-twitter-bot-with-google-spreadsheets-version-04/) for instructions. He has a nice little bot script set up via Google Sheets for you to customize and publish, without need for other server arrangements.

1. find the sheet [here](https://docs.google.com/spreadsheets/d/1Cbg_6pYN04XtDHpDLtxAP3ExQEBL8PYBXBQ1E5_Sq30/copy) and click on “copy” to make a copy of it to your google docs account under “sheets.”

2. enter your app information: 
    - Name of twitter account on line 9
    - Consumer key (line 23)
    - Consumer secret (line 26)
    - Project key (line 32). Click on Tools > Script Editor and then File > Project Properties. You'll find your project key under "info" in the popup box.
    - finally, scroll down to line 37, and copy the Callback URL in the red box. Switch back to your twitter app (apps.twitter.com), and enter that number into the box under "Callback URL" inside your app.
    
3. Whalen’s script has several “styles” to tweet in. For Intimate Fields, we chose to use the “Markov” flavor. Markov chain generators chop up existing text, look for repeated patterns, and then recombine text according to the patterns it finds. Because posies are generic (making use of repetitive tropes and combinations of words) they’re an excellent corpus for Markov remixing. Choose “Markov” on line 43.

4. go into the “Markov” portion of the spreadsheet and delete the Austen text there, replacing it with a posie corpus. We created one consisting of posies from *Loves Garland* and a couple of other full-text historical posie collections (along with a set of 90 phrases from Roland Barthes’ *A Lovers Discourse* and 10 phrases from Bruno Latour's *Aramis*). As a sample, you can find ours under `corpus.txt` in the Intimate Fields twitterbot repository.

5. finally, choose how often you want it to tweet. Twitter gets *very* antsy about high-traffic twitterbots. If you’re going to leave it running for long periods of time you might want to limit tweets to every half hour. Once you’re all set to go, go up to the “bot” menu and select “send test tweet” to make sure everything’s working the way it should. Once it looks right, go back up to the bot menu and tell it to run the script. That’s it!

#### Method 2 (slightly more involved option, Python)

If you want to roll your own, you’ll need to find some good Markov scripts and a Twitter script for posting. We’ve included files for running on Python in the repository. You’ll need two Python packages, **Markovify** and **Tweepy**. You can get them both from Github or (easier) via `pip install`.

1. From the Intimate Fields repository download `markov.py`, `corpus.txt`, `history.txt` and `keys.py` into the same directory.

2. replace the `corpus.py` text with your own, if you want to add extra (or different) posies

3. Open up `keys.py` and replace the blank text with your keys: Consumer Key, Consumer Secret, Access Token and Access Secret from step 2.

4. Open up `markov.py` and replace the twitter account handle at the bottom of the script with your own.

5. Open up Terminal, navigate into the directory with your four files, and run the bot by typing `python markov.py`. If all’s well, your bot will tweet a new posy.

6. Keeping your bot running continuously will depend on your setup. If you’ve got a dedicated Raspberry Pi set up, you can just set up a cron job telling it to run the script every 30 minutes. Or, if you have shell-access hosting somewhere, you can upload the files to your host and run the cron job there.

**Note** *Every environment is different. For Dreamhost, here are a few useful links on your way to setting up the script and running it:*

- [Python for botmakers on dreamhost](https://gist.github.com/moonmilk/8d78032debd16f31a8a9)
- [what to do if you get the insecure platform warning](https://urllib3.readthedocs.org/en/latest/security.html#insecureplatformwarning)
- [installing pyopenssl](https://urllib3.readthedocs.org/en/latest/security.html#openssl-pyopenssl)