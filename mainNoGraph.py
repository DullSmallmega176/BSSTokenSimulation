import random, os, time
from timeit import default_timer as timer

ELAPSETIME = 3600000*2 # ELAPSETIME - how many milliseconds to simulate
# --- bee stats ---
GIFTED = True  # GIFTED - controls if it should take into concideration about inspire
BEE = 'ninja'
# --- mutations ---
BMS = 0     # BMS - Bee Movespeed - affects the bee's movement
BAR = 4     # BAR - Bee Ability Rate - affects the bee's TGC and TAC
# --- player/bee booster stats --- for better accuracy so we don't have to spend quads on testing.
PBAR = 131  # PBAR - Player Bee Ability Rate - your BAR in the system page
PERCBMS = 11  # PERCBMS - Percentage BMS - your total BMS percentage boost. you can do math to find it out.
'''
BaseMovespeed*(1+((level-1)*0.03))*x = ActualBeeSpeed
Ex:
base movespeed - 14
level - 5
actual movespeed = 15.99
x = 1.019770408163 -> round to the nearest 2nd decimal.
x = 1.02 -> my total percentage is 2%
'''
ADDBMS = 0 # ADDBMS - Add BMS - Adding to base movespeed of a bee.
BEELVL = 21 # BEELVL - Bee Level - this increases BMS by 3% per level
# --- extra stats --- this is for beequips and stuff
BBAR = 0  # BBAR - Beequip BAR - extra buffs given from other beequips, no hive bonus
BTOKEN = [] # BTOKEN - Beequip Token - extra token spawn from beequips
# --- creating the token & bee database ---
# TGC - Token General Cooldown - how long before a token can spawn again
# TAC - Token Attempt Cooldown - time it takes for the bee to attempt spawning a token again after falure
# TSR - Token Success Rate - chance of a token spawning per attempt
TOKENLIST = {
    'haste':{'TGC':4.5, 'TAC':4.5, 'TSR':1/3},
    'focus':{'TGC':4.5, 'TAC':4.5, 'TSR':1/3},
    'rage':{'TGC':50, 'TAC':15, 'TSR':1}, # only attacking, so not accurate
    'tokenLink':{'TGC':5, 'TAC':5, 'TSR':1/3},
    'mark':{'TGC':20, 'TAC':5, 'TSR':1/4},
    'babyLove':{'TGC':60, 'TAC':5, 'TSR':1/9},
    'melody':{'TGC':45, 'TAC':15, 'TSR':1/3},
    'bomb':{'TGC':8, 'TAC':4, 'TSR':1/4},
    'boost':{'TGC':4.5, 'TAC':4.5, 'TSR':1/3},
    'honeyGift':{'TGC':120, 'TAC':60, 'TSR':1/4},
    'triangulate':{'TGC':20, 'TAC':10, 'TSR':1/3},
    'markSurge':{'TGC':24, 'TAC':6, 'TSR':1/4},
    'inferno':{'TGC':30, 'TAC':5, 'TSR':1/6},
    'flameFuel':{'TGC':45, 'TAC':15, 'TSR':1/3},
    'summonFrog':{'TGC':50, 'TAC':10, 'TSR':1/4},
    'inflateBalloon':{'TGC':28, 'TAC':8, 'TSR':1/4},
    'surpriseParty':{'TGC':360, 'TAC':15, 'TSR':1/8},
    'targetPractice':{'TGC':24, 'TAC':6, 'TSR':1/4},
    'fuzzBombs':{'TGC':20, 'TAC':10, 'TSR':1/3},
    'pollenHaze':{'TGC':75, 'TAC':15, 'TSR':1/6},
    'beamstorm':{'TGC':20, 'TAC':10, 'TSR':1/3},
    'scratch':{'TGC':12, 'TAC':6, 'TSR':1/4},
    'tabbyLove':{'TGC':120, 'TAC':60, 'TSR':1/5},
    'fetch':{'TGC':140, 'TAC':5, 'TSR':1/2},
    'puppyLove':{'TGC':80, 'TAC':10, 'TSR':1/5},
    'bearMorph':{'TGC':45, 'TAC':15, 'TSR':1/2},
    'pulse':{'TGC':12, 'TAC':6, 'TSR':1/4},
    'bombSync':{'TGC':30, 'TAC':15, 'TSR':1/3},
    'festiveGift':{'TGC':480, 'TAC':30, 'TSR':1/8},
    'glob':{'TGC':6, 'TAC':3, 'TSR':1/3},
    'gumdropBarrage':{'TGC':9, 'TAC':4, 'TSR':1/4},
    'impale':{'TGC':30, 'TAC':1, 'TSR':1},
    'rainCloud':{'TGC':45, 'TAC':20, 'TSR':1/2},
    'tornado':{'TGC':80, 'TAC':10, 'TSR':1/3},
    'glitch':{'TGC':60, 'TAC':10, 'TSR':1/3},
    'mapCorruption':{'TGC':360, 'TAC':15, 'TSR':1/8},
    'mindHack':{'TGC':90, 'TAC':2, 'TSR':1/3},
    'smile':{'TGC':0, 'TAC':15, 'TSR':1}, # guesing this is the 'happy/sad' check
    'festiveMark':{'TGC':300, 'TAC':30, 'TSR':1/6},
    'snowglobeShake':{'TGC':300, 'TAC':30, 'TSR':1/6},
    'inspire':{'TGC':60, 'TAC':5, 'TSR':1/100},
}
'''
speed - the bee's base speed
gather - the bee's gather time 'spinEffect'
token - what the bee can make while gathering
gifted - what the bee can make while gathering and gifted
'''
BEES = {
    'basic':{'speed':14,'gather':4,'token':[], 'gifted':['inspire']},
    'bomber':{'speed':15.4,'gather':4,'token':['bomb'], 'gifted':['inspire']},
    'brave':{'speed':16.8,'gather':4,'token':[], 'gifted':['inspire']},
    'bumble':{'speed':10.5,'gather':4,'token':['bomb'], 'gifted':['inspire']},
    'cool':{'speed':14,'gather':3,'token':['boost'], 'gifted':['inspire']},
    'hasty':{'speed':19.6,'gather':3,'token':['haste'], 'gifted':['inspire']},
    'looker':{'speed':14,'gather':4,'token':['focus'], 'gifted':['inspire']},
    'rad':{'speed':14,'gather':4,'token':['boost'], 'gifted':['inspire']},
    'rascal':{'speed':16.1,'gather':4,'token':['bomb'], 'gifted':['inspire']},
    'stubborn':{'speed':11.9,'gather':4,'token':['mark'], 'gifted':['inspire']},
    'bubble':{'speed':16.1,'gather':4,'token':['bomb'], 'gifted':['inspire']},
    'bucko':{'speed':15.4,'gather':4,'token':['boost'], 'gifted':['inspire']},
    'commander':{'speed':14,'gather':4,'token':['focus', 'bomb'], 'gifted':['inspire']},
    'demo':{'speed':16.8,'gather':4,'token':['bomb'], 'gifted':['inspire']},
    'exhausted':{'speed':10.5,'gather':4.6,'token':['bomb', 'tokenLink'], 'gifted':['inspire']},
    'fire':{'speed':11.2,'gather':4,'token':['bomb'], 'gifted':['inspire']},
    'frosty':{'speed':11.2,'gather':4,'token':['boost', 'bomb'], 'gifted':['inspire']},
    'honey':{'speed':14,'gather':4,'token':['honeyGift'], 'gifted':['inspire']},
    'rage':{'speed':15.4,'gather':4,'token':['tokenLink'], 'gifted':['inspire']}, # rage excluded for now
    'riley':{'speed':15.4,'gather':2,'token':['boost'], 'gifted':['inspire']},
    'shocked':{'speed':19.6,'gather':4,'token':['haste', 'tokenLink'], 'gifted':['inspire']},
    'baby':{'speed':10.5,'gather':5,'token':['babyLove'], 'gifted':['inspire']},
    'carpenter':{'speed':11.2,'gather':3,'token':['mark', 'mark'], 'gifted':['inspire']},
    'demon':{'speed':10.5,'gather':4,'token':['bomb', 'bomb'], 'gifted':['inspire']},
    'diamond':{'speed':14,'gather':4,'token':['boost', 'honeyGift'], 'gifted':['inspire']},
    'lion':{'speed':19.6,'gather':4,'token':['bomb'], 'gifted':['inspire']},
    'music':{'speed':16.1,'gather':4,'token':['melody', 'focus', 'tokenLink'], 'gifted':['inspire']},
    'ninja':{'speed':21,'gather':2,'token':['haste', 'bomb'], 'gifted':['inspire']},
    'shy':{'speed':18.2,'gather':2,'token':['boost', 'bomb'], 'gifted':['inspire']},
    'buoyant':{'speed':14,'gather':5,'token':['bomb','inflateBalloon'], 'gifted':['inspire', 'surpriseParty']},
    'fuzzy':{'speed':11.9,'gather':6,'token':['fuzzBombs', 'bomb'], 'gifted':['inspire', 'pollenHaze']},
    'precise':{'speed':11.2,'gather':4,'token':['targetPractice'], 'gifted':['inspire']},
    'spicy':{'speed':14,'gather':4,'token':['inferno', 'rage'], 'gifted':['inspire', 'flameFuel']},
    'tadpole':{'speed':11.2,'gather':6,'token':['boost', 'summonFrog'], 'gifted':['inspire', 'babyLove']},
    'vector':{'speed':16.24,'gather':4,'token':['mark', 'triangulate'], 'gifted':['inspire', 'markSurge']},
    'bear':{'speed':14,'gather':2,'token':['bearMorph'], 'gifted':['inspire']},
    'cobalt':{'speed':18.2,'gather':4,'token':['pulse', 'bombSync'], 'gifted':['inspire']},
    'crimson':{'speed':18.2,'gather':4,'token':['pulse', 'bombSync'], 'gifted':['inspire']},
    'digital':{'speed':11.9,'gather':4,'token':['glitch', 'mindHack'], 'gifted':['inspire', 'mapCorruption']},
    'festive':{'speed':16.1,'gather':4,'token':['festiveGift', 'mark', 'bomb'], 'gifted':['inspire']},
    'gummy':{'speed':14,'gather':4,'token':['gumdropBarrage', 'glob'], 'gifted':['inspire']},
    'photon':{'speed':21,'gather':2,'token':['beamstorm', 'haste'], 'gifted':['inspire']},
    'puppy':{'speed':16.1,'gather':4,'token':['fetch', 'puppyLove'], 'gifted':['inspire']},
    'tabby':{'speed':16.1,'gather':4,'token':['scratch', 'tabbyLove'], 'gifted':['inspire']},
    'vicious':{'speed':17.5,'gather':4,'token':['impale', 'bomb'], 'gifted':['inspire']},
    'windy':{'speed':19.6,'gather':3,'token':['boost', 'rainCloud', 'tornado'], 'gifted':['inspire']}
}
'''
base - the bee's base {tgc/tac}
pbar - player's bee ability rate in the settings menu
bar - the bee's bar mutation %
bbar - beequip BAR% 'this include hive bonuses'
'''
def adjCooldwn(base, pbar, bar, bbar):
    return base/(((pbar+bbar)/100)*(1+(bar/100)))
'''
base - the bee's base movespeed
addbms - values that adds towards the bee's base movespeed 'mutation included'
percbms - values that multiply towards the bee's movespeed after addbms and mutbms
    oil/smoothie, playtime badge, beequips, gifted hive bonus.
levels - the bee's level.
'''
def adjSpeed(base, addbms, percbms, level):
    return (base+addbms)*(1+(percbms/100))*(1+((level-1)*0.03))

def spinEffect(tsr):
    if random.random() <= tsr:
        return 2
    return 0

def gatherEffect(gather):
    return gather

def movementEffect(walkspeed):
    studs = random.randint(1, 20)*4
    return round((studs/walkspeed)*1000)

os.system('cls')

# --- start the simulation ---
# each itteration will count 1 millisecond towards the supplied elapse time 'eample: 1 day', the itteration won't actually take 1 millisecond.
def simulation(beeName):
    if beeName not in BEES:
        print('invalid bee')
        return
    # getting data
    bee = BEES[beeName]
    speed = adjSpeed(bee['speed'], BMS+ADDBMS, PERCBMS, BEELVL)
    gather = bee['gather']
    tlist = bee['token'] + bee['gifted'] + BTOKEN
    tokens = {} # used as a general value for reset timer
    timers = {} # used as the simulation.
    for token in tlist:
        tokens[token] = {
            'TGC':round(adjCooldwn(TOKENLIST[token]['TGC'], PBAR, BAR, BBAR)*1000),
            'TAC':round(adjCooldwn(TOKENLIST[token]['TAC'], PBAR, BAR, BBAR)*1000),
            'TSR':TOKENLIST[token]['TSR']
        }
        timers[token] = {'TGC':tokens[token]['TGC'],'TAC':tokens[token]['TAC'],'total':0}
    timers['gather'] = 0
    timers['movement'] = movementEffect(speed)
    currentTime = 0
    totalTokens = 0
    print("script has started")
    start = timer()
    while currentTime < ELAPSETIME:
        # decrease cooldown
        for token in timers:
            if token not in ['gather', 'movement']:
                timers[token]['TGC'] = max(0, timers[token]['TGC']-1)
                timers[token]['TAC'] = max(0, timers[token]['TAC']-1)
        if timers['movement'] > 0:
            timers['movement'] -= 1
        elif timers['gather'] == 0:
            timers['movement'] = movementEffect(speed)
        # do token checks
        if timers['gather'] == 0 and timers['movement'] == 0:
            for token in timers:
                if token in ['gather', 'movement']:
                    continue
                if timers[token]['TGC'] > 0 or timers[token]['TAC'] > 0 or not random.random() < tokens[token]['TSR']:
                    continue
                timers[token]['TGC'] = tokens[token]['TGC']
                timers[token]['TAC'] = tokens[token]['TAC']
                timers[token]['total'] += 1
                totalTokens += 1
                break
            timers['gather'] = gather
        if timers['gather'] > 0:
            timers['gather'] -= 1
        currentTime+=1 # one millisecond has passed in the simulation.
    print(f'it took {timer()-start} seconds to simulate {ELAPSETIME/60000} minutes\n')
    minutes = ELAPSETIME/60000
    tokenAverage = totalTokens/minutes
    print(f"{beeName}: BMS: {BMS}, BAR: {BAR}")
    print(f"total tokens produced: {totalTokens}")
    print(f"average tokens per minute: {tokenAverage:.2f}")
    print("total tokens for each token")
    for token in timers:
        if token not in ['gather', 'movement']:
            print(f" {token}: {timers[token]['total']}")

os.system('cls')
simulation('honey')
