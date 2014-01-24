import json
import requests
data = {'temperature':'24.3'}
data_json = json.dumps(data)
payload = {'json_playload': data_json, 'apikey': 'YOUR_API_KEY_HERE'}
r = requests.get('https://homeheat.pythonanywhere.com/ACAMP/default/index', data=payload)
