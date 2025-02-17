import openai
def generate_nickname(profit):
    openai.api_key = "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"
    response = openai.ChatCompletion.create(
        model="gpt-4",
        messages=[{"role": "user", "content": f"Generate a trading nickname for a player who made a profit of {profit} Baht."}]
    )
    nickname = response["choices"][0]["message"]["content"]

    with open("nickname.txt", "w", encoding="utf-8") as file:
        file.write(nickname)

generate_nickname(5000)
