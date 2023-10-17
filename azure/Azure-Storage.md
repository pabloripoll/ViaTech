# Azure Storage Service

https://learn.microsoft.com/en-us/rest/api/storageservices/

https://github.com/azure

## Azure Storage Start Up

Go to https://portal.azure.com

Then select from side panel menu `Storage accounts`

On tab `Create`

Login to Azure account and go to `portal.azure.com/#blade/HubsExtension/BrowseResourceGroups` and on top navigation menu click on `Cloud Shell`

Create Azure Service Principle add the following commands
```bash
$ az ad sp create-for-rbac --name "sp_for_creating_storageAccount" -- role contributor
...
{
  "appId": "798256c4-bbdc-4f7a-a20a-",
  "displayName": "azure-cli-2021-02-10-22-47-08",
  "name": "http://azure-cli-2021-02-10-22-47-08",
  "password": "",
  "tenant": "72f988bf-86f1-41af-91ab-"
}
```

Create a resoruce group
```bash
$ az group create --location westus --name rg_for_storageAccount
...
{
  "id": "/subscriptions/fa628409-59a2-43ed-afde-7b509d932bbd/resourceGroup/rg_for_storageAccount",
  "location": "westus",
  "manageBy": "rg_for_storageAccount",
  "name": "",
  "properties": {
    "provisioningState": "Succeded"
  },
  "tags": "null",
  "type": "Microsoft.Resources/resourcesGroups"
}
```

### Get Access Token

```json

```

## Postman
Azure_storage_acc_env.postman_environment.json
```json
{
	"id": "db953e65-3c4c-4121-b413-316b75767d23",
	"name": "Azure_storage_acc_env",
	"values": [
		{
			"key": "client_id",
			"value": "",
			"enabled": true
		},
		{
			"key": "client_secret",
			"value": "",
			"enabled": true
		},
		{
			"key": "tenantid",
			"value": "",
			"enabled": true
		},
		{
			"key": "resource",
			"value": "",
			"enabled": true
		},
		{
			"key": "subscriptionId",
			"value": "",
			"enabled": true
		},
		{
			"key": "resourceGroupName",
			"value": "",
			"enabled": true
		},
		{
			"key": "accountName",
			"value": "",
			"enabled": true
		},
		{
			"key": "access_token",
			"value": "",
			"enabled": true
		},
		{
			"key": "grant_type",
			"value": "",
			"enabled": true
		}
	],
	"_postman_variable_scope": "environment",
	"_postman_exported_at": "2021-09-23T08:25:19.673Z",
	"_postman_exported_using": "Postman/9.0.2"
}
```

Azure Storage Account.postman_collection.json
```json
{
	"info": {
		"_postman_id": "bfba77ea-dd5a-40a4-93f8-4a603619df84",
		"name": "Azure Storage Account",
		"schema": "https://schema.getpostman.com/json/collection/v2.1.0/collection.json"
	},
	"item": [
		{
			"name": "Get Access Token",
			"event": [
				{
					"listen": "test",
					"script": {
						"exec": [
							"var data = JSON.parse(responseBody);\r",
							"postman.setEnvironmentVariable(\"access_token\", data.access_token);"
						],
						"type": "text/javascript"
					}
				}
			],
			"protocolProfileBehavior": {
				"disableBodyPruning": true
			},
			"request": {
				"method": "GET",
				"header": [],
				"body": {
					"mode": "urlencoded",
					"urlencoded": [
						{
							"key": "client_id",
							"value": "{{client_id}}",
							"type": "text"
						},
						{
							"key": "grant_type",
							"value": "{{grant_type}}",
							"type": "text"
						},
						{
							"key": "client_secret",
							"value": "{{client_secret}}",
							"type": "text"
						},
						{
							"key": "resource",
							"value": "{{resource}}",
							"type": "text"
						}
					]
				},
				"url": {
					"raw": "https://login.microsoftonline.com/{{tenantid}}/oauth2/token",
					"protocol": "https",
					"host": [
						"login",
						"microsoftonline",
						"com"
					],
					"path": [
						"{{tenantid}}",
						"oauth2",
						"token"
					]
				}
			},
			"response": []
		},
		{
			"name": "Create Storage Account",
			"request": {
				"auth": {
					"type": "bearer",
					"bearer": [
						{
							"key": "token",
							"value": "{{access_token}}",
							"type": "string"
						}
					]
				},
				"method": "PUT",
				"header": [],
				"body": {
					"mode": "raw",
					"raw": "{\r\n  \"sku\": {\r\n    \"name\": \"Standard_GRS\"\r\n  },\r\n  \"kind\": \"StorageV2\",\r\n  \"location\": \"australiaeast\"\r\n}",
					"options": {
						"raw": {
							"language": "json"
						}
					}
				},
				"url": {
					"raw": "https://management.azure.com/subscriptions/{{subscriptionId}}/resourceGroups/{{resourceGroupName}}/providers/Microsoft.Storage/storageAccounts/{{accountName}}?api-version=2018-02-01",
					"protocol": "https",
					"host": [
						"management",
						"azure",
						"com"
					],
					"path": [
						"subscriptions",
						"{{subscriptionId}}",
						"resourceGroups",
						"{{resourceGroupName}}",
						"providers",
						"Microsoft.Storage",
						"storageAccounts",
						"{{accountName}}"
					],
					"query": [
						{
							"key": "api-version",
							"value": "2018-02-01"
						}
					]
				}
			},
			"response": []
		}
	]
}
```