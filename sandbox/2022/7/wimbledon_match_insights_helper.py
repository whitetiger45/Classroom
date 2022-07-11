#!/bin/python3
import json, re
import requests, sys, traceback
from pathlib import Path
from subprocess import check_call

#rs = [(1101,1133),(1201,1233),(1301,1333),(2101,2164),(2201,2233),(2301,2333)]
# remaining ranges will be from day 10 - 14
# url: https://www.wimbledon.com/en_GB/matchinsights/index.html
# delete any file that is 3.6K b/c its not any data we're interested in
# rm $(ls -oh | grep "3.6K" | awk '{print $8}')
rs = [(1101,1102)]
def downloadUrl(url,outputFile="blob.txt"):
    print(f"[*] Downloading {url}.")
    try:
        cmd = check_call(["curl", "-L", "-o", f"{outputFile}", f"{url}"],
            encoding="utf-8",errors="ignore")
    except:
        cout("error",f"{traceback.format_exc()}")

wimbledon_match_insights = r"https://www.wimbledon.com/clouddata/match-insights/2022/power-rankings/"
def get_insights():
    for r in rs:
        for insight in range(r[0],r[1]):
            url = wimbledon_match_insights + f"{insight}.json"
            downloadUrl(url,outputFile=f"wimbledon_match_insights_{insight}.json")

#get_insights()
p_ladies = Path("wimbledon_ladies_singles.json")
p_mens = Path("wimbledon_mens_singles.json")
match_ids = lambda line : re.finditer(b"match_id",line)
#[list(match_ids(l)) for l in p_ladies.read_bytes().split(b"\n")]
#[list(match_ids(l)) for l in p_mens.read_bytes().split(b"\n")]
mens_match_ids = [idx for idx,l in enumerate(p_mens.read_bytes().split(b"\n")) if list(match_ids(l))]
ladies_match_ids = [idx for idx,l in enumerate(p_ladies.read_bytes().split(b"\n")) if list(match_ids(l))]
mens_match_ids_and_winners = [(idx,idx+15) for idx in mens_match_ids]
ladies_match_ids_and_winners = [(idx,idx+15) for idx in ladies_match_ids]
mens_winners = []; ladies_winners = []
def get_winners_from_indexes(pathObj,indexes):
    ret = []
    for idx in indexes:
        ret.append((str(pathObj.read_bytes().split(b"\n")[idx[0]])[4:-2],str(pathObj.read_bytes().split(b"\n")[idx[1]])[4:-2]))
    return ret

mens_winners = get_winners_from_indexes(p_mens,mens_match_ids_and_winners)
ladies_winners = get_winners_from_indexes(p_ladies,ladies_match_ids_and_winners)
match_winner = lambda line: 0 if "1" in line else 1
opponent = lambda line: 1 if "1" in line else 0
match_id = lambda line: "wimbledon_match_insights_{}.json".format(re.match('.*:\s\"(\d+)',line).group(1))
def set_filename_and_winner(indexes):
    ret = []
    for idx in indexes:
        ret.append((match_id(idx[0]),match_winner(idx[1]),opponent(idx[1])))
    return ret

mens_winners = set_filename_and_winner(mens_winners)
ladies_winners = set_filename_and_winner(ladies_winners)
#print(f"[DEBUG] ladies winners: {ladies_winners}")
#print(f"[DEBUG] mens winners: {mens_winners}")
all_predictions_men = 0; correct_predictions_mens = 0; incorrect_predictions_mens = 0;
all_predictions_ladies = 0; correct_predictions_ladies = 0; incorrect_predictions_ladies = 0;
def tallyPredictions(**obj):
    for match_info in obj["elements"]:
        text = json.loads(Path(match_info[0]).read_text())
        k1 = list(text.keys())[match_info[1]]
        k2 = list(text.keys())[match_info[2]]
        #print(f"[DEBUG] k1: {k1}")
        #print(f"[DEBUG] k2: {k2}")
        player1_prediction = text[k1]["win_prob_prematch"]
        player2_prediction = text[k2]["win_prob_prematch"]
        #print(f"[DEBUG] p1 prediction: {player1_prediction}")
        #print(f"[DEBUG] p2 prediction: {player2_prediction}")
        if player1_prediction > player2_prediction:
            obj["correctTally"] += 1
        else:
            obj["incorrectTally"] += 1
        obj["totalTally"] += 1
    return obj

mens_predictions = {"elements":mens_winners,
"correctTally":correct_predictions_mens,
"incorrectTally":incorrect_predictions_mens,
"totalTally":all_predictions_men}
mens_predictions = tallyPredictions(**mens_predictions)

ladies_predictions = {"elements":ladies_winners,
"correctTally":correct_predictions_ladies,
"incorrectTally":incorrect_predictions_ladies,
"totalTally":all_predictions_ladies}
ladies_predictions = tallyPredictions(**ladies_predictions)

def report(bracket,obj):
    print(f"[*] {bracket} predictions ({obj['totalTally']} matches):")
    print(f"[*]\t{obj['correctTally']} correct predictions ({(obj['correctTally']/obj['totalTally'])*100:0.2f}%)")
    print(f"[*]\t{obj['incorrectTally']} incorrect predictions ({(obj['incorrectTally']/obj['totalTally'])*100:0.2f}%)")

report("ladies",ladies_predictions)
report("mens",mens_predictions)
men_and_ladies_combined_predictions = {
"correctTally":ladies_predictions["correctTally"]+mens_predictions["correctTally"],
"incorrectTally":ladies_predictions["incorrectTally"]+mens_predictions["incorrectTally"],
"totalTally":ladies_predictions["totalTally"]+mens_predictions["totalTally"]
}
report("mens and ladies", men_and_ladies_combined_predictions)
