import instaloader
import csv

# Credenciais de login
seu_usuario = 'seu_usuario'
sua_senha = 'sua_senha'

# Lista de usuários para os quais você tem permissão explícita
usuarios = ["usuario1", "usuario2", "usuario3", "usuario4", "usuario5"]

# Dicionário para armazenar as interações entre os usuários
interacoes_usuarios = {usuario: {usuario_int: 0 for usuario_int in usuarios} for usuario in usuarios}

# Número de postagens a serem coletadas por usuário
num_postagens = 10

# Crie uma instância do Instaloader
loader = instaloader.Instaloader()

# Autentique-se na conta do Instagram
loader.login(seu_usuario, sua_senha)

# Iterar sobre cada usuário
for usuario in usuarios:
    # Obtenha informações sobre o perfil do usuário
    profile = instaloader.Profile.from_username(loader.context, usuario)
    
    # Obtenha os seguidores do usuário e filtre apenas os que estão na lista original
    seguidores = [follower.username for follower in profile.get_followers() if follower.username in usuarios]
    
    # Obtenha as últimas postagens do usuário
    postagens_usuario = []
    for post in profile.get_posts():
        if len(postagens_usuario) >= num_postagens:
            break
        likes_post = [like.username for like in post.get_likes() if like.username in usuarios]
        comentarios_post = [comment.user.username for comment in post.get_comments() if comment.user.username in usuarios]
        postagens_usuario.append({"likes": likes_post, "comentarios": comentarios_post})
    
    # Adicione interações com outros usuários
    for postagem in postagens_usuario:
        for like in postagem["likes"]:
            interacoes_usuarios[usuario][like] += 1
        for comentario in postagem["comentarios"]:
            interacoes_usuarios[usuario][comentario] += 2

# Salvar o output em um arquivo CSV
with open('output_interacoes.csv', 'w', newline='', encoding='utf-8') as csvfile:
    writer = csv.writer(csvfile, delimiter=';')
    writer.writerow(['usuario'] + usuarios)
    
    for usuario, interacoes in interacoes_usuarios.items():
        valores_interacoes = [str(interacoes[usuario_int]) for usuario_int in usuarios]
        writer.writerow([usuario] + valores_interacoes)

print("Output salvo em 'output_interacoes.csv'.")
