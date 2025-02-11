import openai
def generate_nickname(profit):
    openai.api_key = "your-api-key"
    response = openai.ChatCompletion.create(
        model="gpt-4",
        messages=[{"role": "user", "content": f"Generate a trading nickname for a player who made a profit of {profit} Baht."}]
    )
    nickname = response["choices"][0]["message"]["content"]

    with open("nickname.txt", "w", encoding="utf-8") as file:
        file.write(nickname)

generate_nickname(5000)
